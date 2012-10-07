#include <iostream>
#include <boost/thread/barrier.hpp>

#include "thread/static_prio.hpp"
#include "db/database.hpp"
#include "db/tuple.hpp"
#include "process/remote.hpp"
#include "sched/thread/assert.hpp"
#include "vm/state.hpp"
#include "sched/common.hpp"
#include "utils/time.hpp"

using namespace boost;
using namespace std;
using namespace process;
using namespace vm;
using namespace db;
using namespace utils;

//#define DEBUG_PRIORITIES
// #define PROFILE_QUEUE

#ifdef PROFILE_QUEUE
static atomic<size_t> prio_count(0);
static atomic<size_t> prio_immediate(0);
static atomic<size_t> prio_marked(0);
static atomic<size_t> prio_moved_pqueue(0);
static atomic<size_t> prio_add_pqueue(0);
static atomic<size_t> prio_removed_pqueue(0);
static atomic<size_t> prio_nodes_compared(0);
static atomic<size_t> prio_nodes_changed(0);
#endif

namespace sched
{

void
static_local_prio::assert_end(void) const
{
   assert(!has_work());
   assert(is_inactive());
   assert(all_threads_finished());
   assert_thread_end_iteration();
   assert_static_nodes_end(id);
}

void
static_local_prio::assert_end_iteration(void) const
{
   assert(!has_work());
   assert(is_inactive());
   assert(all_threads_finished());
   assert_thread_end_iteration();
   assert_static_nodes_end_iteration(id);
}

void
static_local_prio::retrieve_prio_tuples(void)
{
	while(!prio_tuples.empty()) {
		work new_work(prio_tuples.pop());
		node_work node_new_work(new_work);
		thread_intrusive_node *to(dynamic_cast<thread_intrusive_node*>(new_work.get_node()));
		
		add_prio_tuple(node_new_work, to, node_new_work.get_tuple());
	}
}

void
static_local_prio::new_agg(work& new_work)
{
   thread_intrusive_node *to(dynamic_cast<thread_intrusive_node*>(new_work.get_node()));
   
   assert_thread_push_work();
   
   node_work node_new_work(new_work);
   to->add_work(node_new_work);
   
   if(!to->in_queue()) {
      add_to_queue(to);
      to->set_in_queue(true);
   }
}

void
static_local_prio::add_prio_tuple(node_work node_new_work, thread_intrusive_node *to, db::simple_tuple *stpl)
{
	const field_num field(state::PROGRAM->get_priority_argument());
	vm::tuple *tpl(stpl->get_tuple());
	heap_priority valp;
	const bool has_prio_tuples(!to->prioritized_tuples.empty());
	tuple_field val(tpl->get_field(field));
	heap_priority min_before;

	if(has_prio_tuples)
		min_before = to->get_min_value();
	
	switch(priority_type) {
		case HEAP_INT_ASC:
		case HEAP_INT_DESC:
			valp.int_priority = val.int_field;
			break;
		case HEAP_FLOAT_ASC:
		case HEAP_FLOAT_DESC:
			valp.float_priority = val.float_field;
			break;
		default: assert(false);
	}

	to->prioritized_tuples.insert(node_new_work, valp);

	if(to != current_node) {
		spinlock::scoped_lock l(to->spin);
			
		if(global_prioqueue::in_queue(to)) {
			assert(!node_queue::in_queue(to));
				
			const heap_priority min_now(to->get_min_value());
				
			assert(has_prio_tuples);

			bool different_priority(false);

			switch(priority_type) {
				case HEAP_INT_DESC:
				case HEAP_INT_ASC: different_priority = min_now.int_priority != min_before.int_priority; break;
				case HEAP_FLOAT_DESC:
				case HEAP_FLOAT_ASC: different_priority = min_now.float_priority != min_before.float_priority; break;
				default: assert(false);
			}
				
			if(different_priority) {
#ifdef PROFILE_QUEUE
				prio_moved_pqueue++;
#endif
				gprio_queue.move_node(to, min_now);
			}
		} else {
			if(node_queue::in_queue(to)) {
#ifdef PROFILE_QUEUE
				prio_removed_pqueue++;
#endif
				queue_nodes.remove(to);
			}
			assert(!node_queue::in_queue(to));
				
#ifdef PROFILE_QUEUE
			prio_add_pqueue++;
#endif
			gprio_queue.insert(to, to->get_min_value());
		}
			
		assert(global_prioqueue::in_queue(to));
		assert(!node_queue::in_queue(to));
			
		if(!to->in_queue())
			to->set_in_queue(true);
	}
}

void
static_local_prio::new_work(const node *, work& new_work)
{
   thread_intrusive_node *to(dynamic_cast<thread_intrusive_node*>(new_work.get_node()));
   
   assert_thread_push_work();
   
   node_work node_new_work(new_work);
	db::simple_tuple *stpl(node_new_work.get_tuple());
	const vm::predicate *pred(stpl->get_predicate());
	
	if(pred->is_global_priority()) {
		add_prio_tuple(node_new_work, to, stpl);
	} else {
   	to->add_work(node_new_work);
		if(!to->in_queue()) {
	      spinlock::scoped_lock l(to->spin);
	      if(!to->in_queue()) {
				if(!global_prioqueue::in_queue(to))
					add_to_queue(to);
	         to->set_in_queue(true);
	      }
	      // no need to put owner active, since we own this node
	      // new_work was called for init or for self generation of
	      // tuples (SEND a TO a)
	      // the lock is needed in order to make sure
	      // the node is not put multiple times on the queue
	   }   
   }

	assert(to->in_queue());
}

void
static_local_prio::new_work_other(sched::base *, work& new_work)
{
   assert(is_active());
   
   thread_intrusive_node *tnode(dynamic_cast<thread_intrusive_node*>(new_work.get_node()));
   
   assert(tnode->get_owner() != NULL);
   
   assert_thread_push_work();
   
   node_work node_new_work(new_work);
	db::simple_tuple *stpl(node_new_work.get_tuple());
	const vm::predicate *pred(stpl->get_predicate());
	
	if(pred->is_global_priority()) {
		static_local_prio *owner(dynamic_cast<static_local_prio*>(tnode->get_owner()));
		
		owner->prio_tuples.push(new_work);
		
   	if(this != owner) {
      	spinlock::scoped_lock l2(owner->lock);
         
      	if(owner->is_inactive() && owner->has_work())
      	{
         	owner->set_active();
         	assert(owner->is_active());
      	}
   	} else {
      	assert(is_active());
   	}
	} else {
   	tnode->add_work(node_new_work);
   
		spinlock::scoped_lock l(tnode->spin);
	
   	if(!tnode->in_queue() && tnode->has_work()) {
			static_local_prio *owner(dynamic_cast<static_local_prio*>(tnode->get_owner()));
		
			tnode->set_in_queue(true);
			if(!global_prioqueue::in_queue(tnode))
				owner->add_to_queue(tnode);

      	if(this != owner) {
         	spinlock::scoped_lock l2(owner->lock);
         
         	if(owner->is_inactive() && owner->has_work())
         	{
            	owner->set_active();
            	assert(owner->is_active());
         	}
      	} else {
         	assert(is_active());
      	}
         
      	assert(tnode->in_queue());
   	}
	}
   
#ifdef INSTRUMENTATION
   sent_facts++;
#endif
}

void
static_local_prio::new_work_remote(remote *, const node::node_id, message *)
{
   assert(false);
}

void
static_local_prio::generate_aggs(void)
{
   iterate_static_nodes(id);
}

bool
static_local_prio::busy_wait(void)
{
   ins_idle;
   
   while(!has_work()) {
      BUSY_LOOP_MAKE_INACTIVE()
      BUSY_LOOP_CHECK_TERMINATION_THREADS()
   	retrieve_prio_tuples();
	}
	
   // since queue pushing and state setting are done in
   // different exclusive regions, this may be needed
   set_active_if_inactive();
   ins_active;
   assert(is_active());
   assert(has_work());
   
   return true;
}

bool
static_local_prio::terminate_iteration(void)
{
   START_ROUND();
   
   if(has_work())
      set_active();
   
   END_ROUND(
      more_work = num_active() > 0;
   );
}

void
static_local_prio::finish_work(const work& work)
{
   base::finish_work(work);
   
   assert(current_node != NULL);
   assert(current_node->in_queue());
   assert(current_node->get_owner() == this);
}

bool
static_local_prio::check_if_current_useless(void)
{
	if(!prio_queue.empty() && current_node->is_in_prioqueue() && current_node->has_work()) {
		// there could be higher priority nodes around
		const heap_priority current_min(prio_queue.min_value());

		if(current_min.int_priority < current_node->get_priority_level()) {
			// put this node back into the priority queue and use the higher priority one
			heap_priority node_pr;
			node_pr.int_priority = current_node->get_priority_level();
			assert(current_node->__intrusive_priority.int_priority == current_node->get_priority_level());
#ifdef DEBUG_PRIORITIES
			//cout << "Node in queue has higher priority: " << current_min.int_priority << " vs " << node_pr.int_priority << endl;
#endif
			prio_queue.insert(current_node, node_pr);
			current_node = prio_queue.pop();
		}
	} else if(!gprio_queue.empty() && current_node->has_prio_work()) {
		const heap_priority current_min(gprio_queue.min_value());
		const heap_priority node_min(current_node->get_min_value());
		
#ifdef PROFILE_QUEUE
		prio_nodes_compared++;
#endif

		assert(!current_node->is_in_prioqueue());

		bool is_current_best(false);

		switch(priority_type) {
			case HEAP_INT_ASC: is_current_best = (current_min.int_priority < node_min.int_priority); break;
			case HEAP_INT_DESC: is_current_best = (current_min.int_priority > node_min.int_priority); break;
			case HEAP_FLOAT_ASC: is_current_best = (current_min.float_priority < node_min.float_priority); break;
			case HEAP_FLOAT_DESC: is_current_best = (current_min.float_priority > node_min.float_priority); break;
			default: assert(false);
		}
		
		if(is_current_best) {
			// put back into priority queue
			gprio_queue.insert(current_node, node_min);
			assert(global_prioqueue::in_queue(current_node));
			current_node = gprio_queue.pop();
#ifdef PROFILE_QUEUE
			prio_nodes_changed++;
#endif
		}
		
		assert(current_node->in_queue());
		assert(current_node->has_work());
		return false;
	}
	
   if(!current_node->has_work()) {
      spinlock::scoped_lock lock(current_node->spin);
      
      if(!current_node->has_work()) {
         if(!node_queue::in_queue(current_node)) {
            current_node->set_in_queue(false);
				current_node->set_is_in_prioqueue(false);
				current_node->set_priority_level(0);
            assert(!current_node->in_queue());
         }
			current_node = NULL;
         return true;
      }
   }
   
   assert(current_node->has_work());
   return false;
}

bool
static_local_prio::set_next_node(void)
{
   if(current_node != NULL)
      check_if_current_useless();
   
   while (current_node == NULL) {   
      if(!has_work()) {
         if(!busy_wait())
            return false;
      }
      
      assert(has_work());

		retrieve_prio_tuples();
		
		if(!gprio_queue.empty()) {
			current_node = gprio_queue.pop();
			goto loop_check;
		}
#ifdef PRIO_OPT
		if(!prio_queue.empty()) {
			current_node = prio_queue.pop();
		} else if(!queue_nodes.empty()) {
			const bool suc(queue_nodes.pop(current_node));
			if(!suc)
				continue;
		}
#else
		{
			const bool suc(queue_nodes.pop(current_node));
		
			assert(suc);
		}
#endif

loop_check:
      assert(current_node->in_queue());
      assert(current_node != NULL);
      
      check_if_current_useless();
   }
   
   ins_active;
   
   assert(current_node != NULL);
   
   return true;
}

bool
static_local_prio::get_work(work& new_work)
{
	retrieve_prio_tuples();
	
   if(!set_next_node())
      return false;
      
   set_active_if_inactive();
   assert(current_node != NULL);
   assert(current_node->in_queue());
   assert(current_node->has_work());
   
	node_work unit;
	
	if(current_node->has_normal_work())
		unit = current_node->get_work();
	else
		unit = current_node->prioritized_tuples.pop();
   
   new_work.copy_from_node(current_node, unit);
   
   assert(new_work.get_node() == current_node);
   
   assert_thread_pop_work();
   
   return true;
}

void
static_local_prio::end(void)
{
#ifndef PRIO_NORMAL
#if defined(DEBUG_PRIORITIES) && defined(PROFILE_QUEUE) && defined(PRIO_OPT)
	cout << "prio_immediate: " << prio_immediate << endl;
	cout << "prio_marked: " << prio_marked << endl;
	cout << "prio_count: " << prio_count << endl;
#endif
#ifdef PROFILE_QUEUE
	if(state::PROGRAM->has_global_priority()) {
		cout << "Moved nodes in priority queue count: " << prio_moved_pqueue << endl;
		cout << "Removed from normal queue count: " << prio_removed_pqueue << endl;
		cout << "Added to priority queue count: " << prio_add_pqueue << endl;
		cout << "Changed nodes count: " << prio_nodes_changed << endl;
		cout << "Compared nodes count: " << prio_nodes_compared << endl;
	}
#endif
#endif
	
#if defined(PRIO_OPT) && defined(DEBUG_PRIORITIES)
	size_t total_prioritized(0);
	size_t total_nonprioritized(0);
	
   database::map_nodes::iterator it(state::DATABASE->get_node_iterator(remote::self->find_first_node(id)));
   database::map_nodes::iterator end(state::DATABASE->get_node_iterator(remote::self->find_last_node(id)));
   
   for(; it != end; ++it)
   {
      thread_intrusive_node *cur_node((thread_intrusive_node*)it->second);
		
		if(cur_node->has_been_prioritized)
			++total_prioritized;
		else
			++total_nonprioritized;
	}
	
	cout << "Number of prioritized nodes: " << total_prioritized << endl;
	cout << "Number of non prioritized nodes: " << total_nonprioritized << endl;
#endif
}

void
static_local_prio::add_node_priority(node *n, const int priority)
{
#ifdef PRIO_OPT
	thread_intrusive_node *tn((thread_intrusive_node*)n);

	const int old_prio(tn->get_priority_level());

	set_node_priority(n, old_prio + priority);
#else
	(void)n;
	(void)priority;
#endif
}

void
static_local_prio::set_node_priority(node *n, const int priority)
{
#ifdef PRIO_NORMAL
	(void)n;
#elif defined(PRIO_HEAD)
	(void)n;
#elif defined(PRIO_OPT)
	thread_intrusive_node *tn((thread_intrusive_node*)n);
	
	tn->has_been_prioritized = true;
	
	if(tn->in_queue()) {
#ifdef PROFILE_QUEUE
		prio_immediate++;
#endif
		if(tn->is_in_prioqueue()) {
			if(tn != current_node) {
				if(tn->get_priority_level() != priority) {
					heap_priority pr;
					pr.int_priority = priority;
#ifdef DEBUG_PRIORITIES
					//cout << "Changing node priority " << tn->get_id() << " (" << tn->get_priority_level() << ") to" << priority << endl;
#endif
					tn->set_priority_level(priority);
					prio_queue.move_node(tn, pr);
				}
			}
		} else {
			tn->set_priority_level(priority);
#ifdef DEBUG_PRIORITIES
			//cout << "Add node " << tn->get_id() << " with priority " << priority << endl;
#endif
			if(tn != current_node) {
				queue_nodes.remove(tn);
				add_to_priority_queue(tn);
			} else {
				// add_to_priority_queue already does this...
				tn->set_is_in_prioqueue(true);
			}
		}
		assert(tn->is_in_prioqueue());
		assert(tn->get_priority_level() == priority);
	} else {
#ifdef PROFILE_QUEUE
		prio_marked++;
#endif
		assert(tn != current_node);
		tn->set_priority_level(priority);
		tn->mark_priority();
	}
#endif
	
#ifdef PROFILE_QUEUE
	prio_count++;
#endif
}

void
static_local_prio::init(const size_t)
{
	if(state::PROGRAM->has_global_priority()) {
		predicate *p(state::PROGRAM->get_priority_predicate());
		const field_num field(state::PROGRAM->get_priority_argument());

		switch(p->get_field_type(field)) {
			case FIELD_INT:
				if(state::PROGRAM->is_global_priority_asc())
					priority_type = HEAP_INT_ASC;
				else
					priority_type = HEAP_INT_DESC;
				break;
			case FIELD_FLOAT:
				if(state::PROGRAM->is_global_priority_asc())
					priority_type = HEAP_FLOAT_ASC;
				else
					priority_type = HEAP_FLOAT_DESC;
				break;
			default:
				assert(false);
		}
	} else {
		// never used
		priority_type = HEAP_INT_ASC;
	}

	gprio_queue.set_type(priority_type);

   database::map_nodes::iterator it(state::DATABASE->get_node_iterator(remote::self->find_first_node(id)));
   database::map_nodes::iterator end(state::DATABASE->get_node_iterator(remote::self->find_last_node(id)));
   
   for(; it != end; ++it)
   {
      thread_intrusive_node *cur_node((thread_intrusive_node*)it->second);
      cur_node->set_owner(this);
      
      init_node(cur_node);

		cur_node->prioritized_tuples.set_type(priority_type);
      
      assert(cur_node->get_owner() == this);
      assert(cur_node->in_queue());
      assert(cur_node->has_work());
   }
   
   threads_synchronize();
}

static_local_prio*
static_local_prio::find_scheduler(const node *n)
{
   return (static_local_prio*)ALL_THREADS[remote::self->find_proc_owner(n->get_id())];
}

simple_tuple_list
static_local_prio::gather_active_tuples(db::node *node, const vm::predicate_id pred)
{
	simple_tuple_list ls;
	thread_intrusive_node *no((thread_intrusive_node*)node);
	predicate *p(state::PROGRAM->get_predicate(pred));
	
	typedef thread_node::queue_type fact_queue;
	
	if(p->is_global_priority()) {
		typedef thread_intrusive_node::prio_tuples_queue prio_queue;
		for(prio_queue::const_iterator it(no->prioritized_tuples.begin()),
				end(no->prioritized_tuples.end());
			it != end; ++it)
		{
			node_work w(*it);
			simple_tuple *stpl(w.get_tuple());
		
			if(!stpl->must_be_deleted())
				ls.push_back(stpl);
		}
	} else {
		for(fact_queue::const_iterator it(no->queue.begin()), end(no->queue.end()); it != end; ++it) {
			node_work w(*it);
			simple_tuple *stpl(w.get_tuple());
		
			if(!stpl->must_be_deleted() && stpl->get_predicate_id() == pred)
				ls.push_back(stpl);
		}
	}
	
	return ls;
}

void
static_local_prio::write_slice(statistics::slice& sl) const
{
#ifdef INSTRUMENTATION
   base::write_slice(sl);
   sl.work_queue = queue_nodes.size();
#else
   (void)sl;
#endif
}

static_local_prio::static_local_prio(const vm::process_id _id):
   base(_id),
	prio_queue(HEAP_INT_DESC),
   current_node(NULL)
{
}

static_local_prio::~static_local_prio(void)
{
}
   
vector<sched::base*>&
static_local_prio::start(const size_t num_threads)
{
   init_barriers(num_threads);
   
   for(process_id i(0); i < num_threads; ++i)
      add_thread(new static_local_prio(i));
      
   return ALL_THREADS;
}
   
}
