#include "stdlib.h"



typedef struct node{

	int data;
	
	struct node * next;

} t_node , * t_list ;

int list_len(t_node * list);

t_node * create_node(int data);

t_node * add_node(int data, t_node * prev_node);

t_node * remove_node(t_node * prev_node);

t_node * free_list(t_node * node);

t_node * free_list_rec(t_node * node);

int get_first(t_node * node);

void show_list(t_node * node);

void show_list_rec(t_node * node);


