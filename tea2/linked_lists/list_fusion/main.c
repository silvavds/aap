#include <stdio.h>
#include <stdlib.h>

#include "list.h"

t_node * join(t_node * left, t_node * right){

	t_node * result = NULL;
	
	if( left == NULL ){
		return right;
	}
	else if( right == NULL ){
		return left;
	}
	
	if(left->data <= right-> data){
		result = left;
		result->next = join(left->next, right);
	}
	else{	
		result = right;
		result->next = join(left, right->next);
	}
		
		
	return result;		
}

// make a merge sort with lists
t_node * fusion(t_node * list, int length){
	t_node * list_right = list;
	int i;			
	// if it is larger than 1 it can be divided
	
	if(length > 1){
		// the idea is to divide the initial list into 2 smaller lists
		int half = length/2;
		
		for(i = 0; i < half-1; i++)
			list_right = list_right->next;
		
		t_node * aux = list_right->next;
		list_right->next = NULL;
		list_right = aux;

		//printf("pre \n");		
		//show_list(list);
		//show_list(list_right);
					
		list = fusion(list, half);
		list_right = fusion(list_right, length-half);	
		
		//printf("post \n");
		//show_list(list);
		//show_list(list_right);
		
		// make fusion here
		list = join(list, list_right);
		//printf("joined: %p \n", list);
		//show_list(list);
	}	
	else{
		//show_list(list);
	}
	
	//printf("start joining \n");
	//show_list(list);		
	// if it can no longer be divided , then starts merging process
	return list;
}


int main(){
	
	t_node * list1 = create_node(99);	
	list1 = add_node(31, list1);
	list1 = add_node(11, list1);
	list1 = add_node(-50, list1);
	list1 = add_node(9, list1);
	list1 = add_node(888, list1);
	list1 = add_node(22, list1);
	list1 = add_node( 5, list1);
	list1 = add_node(91123, list1);
	list1 = add_node(88, list1);
	list1 = add_node(2, list1);
	list1 = add_node(-88, list1);
	list1 = add_node(112, list1);
	list1 = add_node( 5, list1);
	list1 = add_node(222, list1);
	list1 = add_node( 15, list1);
		
	//show_list(list1);
	//show_list(list2);
	
	
	list1 = fusion(list1, list_len(list1));
	
	show_list(list1);
					
	return 0;
}





