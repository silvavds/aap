#include <stdio.h>
#include <string.h>
#include <assert.h>

//#define CLEAR2CONTINUE
#include "../include/traces.h" 

// C'est dans le fichier elt.h qu'on doit choisir l'implémentation des T_elt
#include "elt.h"	//T_elt

// implémentation des piles contigüe dynamique
#include "stack_cd.h"

typedef struct sized_array{

	int data[3];
	int len;

} sized_array ;

void show2lists(T_stack * list1, T_stack * list2, int j);

void one_step(sized_array * num){
	int i = 0;
	sized_array new;

	new.len = num->len;
	
	for(i = 0; i < (num->len-1) ; i++){
		new.data[i] = num->data[i+1];	
	}
	new.data[new.len-1] = num->data[0];
	
	for(i = 0; i < (num->len) ; i++){
		num->data[i] = new.data[i];
	}
}

void put_botton(T_stack *list1, int element){
	int i, tam = list1->sp;
	T_stack list2 = newStack(10);
	
	for(i = 0 ; i < tam ; i++){
		push(pop(list1), &list2);
	}
	push(element, list1);
	for(i = 0 ; i < tam ; i++){
		push(pop(&list2), list1);
	}
}

int search(T_stack exp, T_stack num){
	int i,j;
	//show2lists(&exp, &num, 0);
	int size = num.sp; 
				
	//for(i = 0 ; i < num.sp ; i++){					
	for(i = 0 ; i < num.sp ; i++){					

		push(pop(&num), &exp);
		
		search(exp, num);
			
		put_botton(&num, pop(&exp) );

	}
	
	show2lists(&exp, &num, i);		
	return 0;
}

int main(int argc, char ** argv) {
	T_stack exp = newStack(10);
	T_stack num = newStack(10);
	
	push(4, &num); push(3, &num); push(2, &num); push(1, &num);
	
	search(exp, num);

	return 0;
}

void show2lists(T_stack * list1, T_stack * list2, int j){
	int i;
	
	printf("exp: [size=%2d] ", list1->sp);
	for(i = 0 ; i < list1->sp; i++)
		printf("[%2d]", list1->data[i]);
	for(i = list1->sp; i < list1->nbMaxElt; i++)
		printf("[  ]");
		
	printf(" | ");
	printf("num: [size=%2d] ", list2->sp);
	for(i = 0 ; i < list2->sp; i++)
		printf("[%2d]", list2->data[i]);
	for(i = list2->sp; i < list2->nbMaxElt; i++)
		printf("[  ]");

	printf("[ %d ]\n", j);
}



