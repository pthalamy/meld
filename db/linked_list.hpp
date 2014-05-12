#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

#include "vm/tuple.hpp"
#include "vm/predicate.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include <iostream>

using namespace std;

extern "C" {  
  struct Node* search_in_list(struct linked_list *ls, void *tpl, struct Node **prev);
  int delete_from_list(struct linked_list *ls, void *tpl);
  void add_last(struct linked_list *ls, void *tpl);
  struct Node* create_list(struct linked_list *ls, void *tpl, void *pred);
}

void
print_tuple(void *tpl, void *pred) 
{
  vm::tuple *print_tpl = (vm::tuple*) tpl;
  vm::predicate *print_pred = (vm::predicate*) pred;
  print_tpl->print(cout, print_pred);
}

bool 
list_tuple_equal(void* tpll, void* tpla, void *preda)
{
  vm::tuple *ls_tpl = (vm::tuple*) tpll;
  vm::tuple *ext_tpl = (vm::tuple*) tpla;
  vm::predicate *pred = (vm::predicate*) preda;
  return (ls_tpl->equal(*ext_tpl, pred));
}

#endif
