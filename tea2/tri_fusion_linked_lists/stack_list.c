#include <stdlib.h>
#include <stdio.h>

#include "stack_list.h"

t_stack * create_stack(int data){
	
	t_stack * pilha = (t_stack *)malloc(sizeof(t_stack *));
	pilha->top_node = create_node(data);
	pilha->sp = 1;
	
	return pilha;
}

t_stack * push(int data, t_stack * stack){

	stack->top_node = add_node(data, stack->top_node);
	stack->sp += 1;
	
	return stack;
}

int pop(t_stack * stack){
	if(stack->sp > 0){
		t_node * old = stack->top_node;	
		stack->top_node = stack->top_node->next;
		int data = old->data;
		
		free(old);
		
		return data;
	}
	
	return -1;
}

void show_stack(t_stack * stack){
	show_list(stack->top_node);
	printf("End of show_stack with [%d] elements \n", stack->sp);
}

