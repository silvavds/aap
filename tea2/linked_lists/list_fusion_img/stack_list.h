#include <stdlib.h>
#include "list.h"

typedef struct stack_type {
	int sp;
	t_node * top_node;
} t_stack;

t_stack * create_stack(int data);

t_stack * push(int data, t_stack * stack);

int pop(t_stack * stack);

void show_stack(t_stack * stack);
