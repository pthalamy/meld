
#include "sched/local/serial.hpp"
#include "process/remote.hpp"
#include "sched/local/serial.hpp"
#include "sched/common.hpp"

using namespace db;
using namespace vm;
using namespace process;

namespace sched
{
   
void
serial_local::new_work(node *from, node *_to, const simple_tuple *tpl, const bool is_agg)
{
   assert(_to != NULL);
   assert(tpl != NULL);
   
   serial_node *to(dynamic_cast<serial_node*>(_to));
   
   to->add_work(tpl, is_agg);
   
   if(!to->in_queue()) {
      to->set_in_queue(true);
      queue_nodes.push(to);
   }
}
   
void
serial_local::assert_end(void) const
{
   assert(!has_work());
   assert_static_nodes(id);
}

void
serial_local::assert_end_iteration(void) const
{
   assert(!has_work());
   assert_static_nodes(id);
}

bool
serial_local::get_work(work_unit& work)
{  
   if(current_node != NULL) {
      // holding a node
      if(!current_node->has_work()) {
         current_node->set_in_queue(false);
         current_node = NULL;
         if(!has_work())
            return false;
         current_node = queue_nodes.pop();
      }
   } else {
      if(!has_work())
         return false;
      current_node = queue_nodes.pop();
      assert(current_node->has_work());
   }
   
   assert(current_node != NULL);
   assert(current_node->has_work());
   assert(current_node->in_queue());
   
   node_work_unit unit(current_node->get_work());
   
   work.work_tpl = unit.work_tpl;
   work.agg = unit.agg;
   work.work_node = current_node;
   
   return true;
}

bool
serial_local::terminate_iteration(void)
{
   generate_aggs();

   return has_work();
}

void
serial_local::generate_aggs(void)
{
   iterate_static_nodes(id);
}

void
serial_local::init(const size_t)
{
   database::map_nodes::iterator it(state::DATABASE->get_node_iterator(remote::self->find_first_node(id)));
   database::map_nodes::iterator end(state::DATABASE->get_node_iterator(remote::self->find_last_node(id)));
   
   for(; it != end; ++it)
   {
      serial_node *cur_node(dynamic_cast<serial_node*>(it->second));
      
      init_node(cur_node);
      
      assert(cur_node->in_queue());
      assert(cur_node->has_work());
   }
}

}