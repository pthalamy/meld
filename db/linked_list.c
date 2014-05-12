#include "linked_list.hpp"

#define VM_TUPLE_PTR void*
#define VM_PRE_PTR void*

struct Node
{
  VM_TUPLE_PTR tuplePtr;
  struct Node *next;
};

struct linked_list 
{
  
  struct Node *head;
  struct Node *tail;
  
  VM_PRE_PTR root_predicate;
  
};

struct Node* 
search_in_list(struct linked_list *ls, VM_TUPLE_PTR tpl, struct Node **prev)
{
  struct Node *ptr = ls->head;
  struct Node *tmp = NULL;
  bool found = false;
      
  while(ptr != NULL) {
    if(list_tuple_equal(ptr->tuplePtr, tpl, ls->root_predicate)) {
      found = true;
      break;
    }
    else {
      tmp = ptr;
      ptr = ptr->next;
    }
  }
  
  if(true == found) {
    if(prev)
      *prev = tmp;
    return ptr;
  }
  else {
    return NULL;
  }
}

int 
delete_from_list(struct linked_list *ls, VM_TUPLE_PTR tpl)
{
  struct Node *prev = NULL;
  struct Node *del = NULL;

  del = search_in_list(ls, tpl, &prev);
  if(del == NULL)
    return -1;
  else {
    if(prev != NULL)
      prev->next = del->next;
      
    if(del == ls->tail)
      ls->tail = prev;
    else if(del == ls->head)
      ls->head = del->next;
  }

free(del);
del = NULL;

return 0;
}
  
void 
add_last(struct linked_list *ls, VM_TUPLE_PTR tpl) 
{
  Node *newNode = (struct Node*)malloc(sizeof(struct Node));
 
  newNode->tuplePtr = tpl;
  newNode->next = NULL;

  if(ls->head == NULL)
    ls->head = newNode;
  else
    ls->tail->next = newNode;
    
  ls->tail = newNode;
}
  
struct Node* 
create_list(struct linked_list *ls, VM_TUPLE_PTR tpl, VM_PRE_PTR pred)
{
  ls->root_predicate = pred;
  struct Node *ptr = (struct Node*)malloc(sizeof(struct Node));
  
  assert(ptr != NULL);
  
  ptr->tuplePtr = tpl;
  ptr->next = NULL;
  ls->head = ptr;
  
  return ptr;
}

void 
print_list(struct linked_list *ls)
{
  struct Node *ptr = ls->head;

  printf("\n ------- Beginning of list ------- \n");
  while(ptr != NULL) {
    print_tuple(ptr->tuplePtr, ls->root_predicate);
    ptr = ptr->next;
  }
  printf("\n ------- End of List ------- \n");

  return;
}
