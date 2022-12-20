#include <stdlib.h>
#include <stdio.h>

#include "list.h"

//study ASSERT
/*
typedef struct node{

	int data;
	struct node * next;
	
} t_node , * t_list ;
*/

int list_len(t_node * list){
	int i=0;
	
	while(list != NULL){
		list = list->next;
		i++;
	}
	
	return i;
}

// creates a new node with specified data value
t_node * create_node(int data){
	
	t_node * node = (t_node *)malloc(sizeof(t_node));

	node->data = data;
	node->next = NULL;
	
	return node;
}

// adds a new node that points to existing node
t_node * add_node(int data, t_node * prev_node){
	
	t_node * node = (t_node *)malloc(sizeof(t_node));

	node->data = data;
	node->next = prev_node;
	
	return node;
}

// removes previously created node
t_node * remove_node(t_node * prev_node){
	
	t_node * new = prev_node->next;
	free(prev_node);

	return new;
}

// returns the first element of a node
int get_first(t_node * node){
	return node->data;
}

// frees a whole list
t_node * free_list(t_node * node){
		
	while( node != NULL ){
		t_node * next = node->next;			
		free(node);	
		node = next;
	}	
	
	return node;
}

// frees a whole list recursively
t_node * free_list_rec(t_node * node){
		
	if( node != NULL ){
		t_node * next = node->next;			
		free(node);	
		node = free_list_rec(next);
	}	
	
	return node;
}


// shows whole list
void show_list(t_node * node){
	int i = 0;
	
	while(node != NULL){
		printf("index[%3d] | actual: [%p] | data: [%5d] | next: [%p] \n", i, node, node->data, node->next);
		node = node->next;
		i++;
	}
	printf("End of show_list \n");
	
}

// shows whole list recursively
void show_list_rec(t_node * node){
	
	if(node != NULL){
		printf("index[%3d] | actual: [%p] | data: [%5d] | next: [%p] \n", 0, node, node->data, node->next);	
		
		if(node->next != NULL)	
			show_list_rec(node->next);
	}
	
			
}



