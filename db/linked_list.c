#include "linked_list.hpp"

list_node* 
search_in_list(linked_list *ls, VM_TUPLE_PTR tpl, list_node **prev)
{
  list_node *ptr = ls->head;
  list_node *tmp = NULL;
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
delete_from_list(linked_list *ls, VM_TUPLE_PTR tpl)
{
  list_node *prev = NULL;
  list_node *del = NULL;

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
add_last(linked_list *ls, VM_TUPLE_PTR tpl) 
{
  Node *newNode = (list_node*)malloc(sizeof(list_node));
 
  newNode->tuplePtr = tpl;
  newNode->next = NULL;

  if(ls->head == NULL)
    ls->head = newNode;
  else
    ls->tail->next = newNode;
    
  ls->tail = newNode;
}
  
list_node* 
create_list(linked_list *ls, VM_TUPLE_PTR tpl, VM_PRE_PTR pred)
{
  ls->root_predicate = pred;
  list_node *ptr = (list_node*)malloc(sizeof(list_node));
  
  assert(ptr != NULL);
  
  ptr->tuplePtr = tpl;
  ptr->next = NULL;
  ls->head = ptr;
  
  return ptr;
}

void 
print_list(linked_list *ls)
{
  list_node *ptr = ls->head;

  printf("\n ------- Beginning of list ------- \n");
  while(ptr != NULL) {
    print_tuple(ptr->tuplePtr, ls->root_predicate);
    ptr = ptr->next;
  }
  printf("\n ------- End of List ------- \n");

  return;
}
