#include "rpn.h"
#include "elt.h"	//T_elt

void show2lists(T_stack * list1, T_stack * list2, int j);
void show1list(T_stack * list1, int res);
void put_botton(T_stack *list1, T_elt element);
int is_valid(T_stack * exp);
int has_op(T_stack * exp);
T_elt compute(T_stack exp_);
T_stack search(T_stack * exp, T_stack * num, int target, T_stack * best);
void show_operations(T_stack * list1, int res);