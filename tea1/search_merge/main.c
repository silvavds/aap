#include <stdio.h>
#include <string.h>
#include <assert.h>

//#define CLEAR2CONTINUE
//#include "../include/traces.h" 

// C'est dans le fichier elt.h qu'on doit choisir l'implémentation des T_elt
#include "elt.h"	//T_elt

// implémentation des piles contigüe dynamique
#include "stack_cd.h"

void show2lists(T_stack * list1, T_stack * list2, int j);

void put_botton(T_stack *list1, T_elt element){
	int i, tam = list1->sp;
	T_stack list2 = newStack(15);
	
	for(i = 0 ; i < tam ; i++)push(pop(list1), &list2);
	push(element, list1);
	for(i = 0 ; i < tam ; i++)push(pop(&list2), list1);
	
	freeStack(&list2);
}

int is_valid(T_stack * exp){

	int i, opr=0, num=0;	
	T_elt aux;
	T_stack exp2 = *exp;
	int tam = exp2.sp;
	
	for(i = 0 ; i < tam ; i++){
	
		aux = pop(&exp2);
	
		if( aux.status == 'O' )opr++;
		else num++;
	}
	
	if(num > opr)return (num - opr);
	
	else return 0;
	
}

int has_op(T_stack * exp){
	
	int i;
	T_elt aux;
	int tam = exp->sp;
	
	T_stack exp2 = *exp;
	
	for(i = 0 ; i < tam ; i++){
		aux = pop(&exp2);
		if( aux.status == 'O' )
			return 1;
	}
		
	return 0;
}

int search(T_stack * exp, T_stack * num){
	int i;

	//show2lists(&exp, &num, 0);
	
	// tests all possible (num+ops) only a single time
	for(i = 0 ; i < num->sp ; i++){					
			
		T_stack num_ = *num;
		T_elt aux = pop(num); 
		
		if( has_op(exp) ){
			
			if( aux.status != 'O' ){
				put_botton(num, aux );	
			}
			else{
				push(aux, exp);
						
				if(is_valid(exp))	
					search(exp, &num_);
					
				put_botton(num, pop(exp) );
			}
		}
		else{
			push(aux, exp);
				
			if( aux.status != 'O' ){
				pop(&num_);
			}
				
			if(is_valid(exp))	
				search(exp, &num_);
				
			put_botton(num, pop(exp) );
		}
					
	}
	int aux = is_valid(exp);
	//int aux = 1;
	if(aux == 1)show2lists(exp, num, i);		
	
	return 0;
}


int main(int argc, char ** argv) {
	T_stack exp = newStack(12);
	T_stack num = newStack(12);
		
	T_elt plus =  {'+','O'};
	T_elt minus = {'-','O'};
	T_elt times = {'*','O'};
	T_elt div =   {'/','O'};
	T_elt one =   {1,'V'};
	T_elt two =   {2,'V'};
	T_elt three = {3,'V'};
	T_elt four =  {4,'V'};
	T_elt five =  {5,'V'};
	T_elt six =  {6,'V'};
	
	//push(plus, &num); push(three, &num); push(two, &num); push(one, &num);
	push(plus, &num); push(minus, &num); push(times, &num); push(div, &num); 
	push(six, &num); push(five, &num); push(four, &num); push(three, &num); push(two, &num); push(one, &num);
	
	
	search(&exp, &num);

	return 0;
}


void show2lists(T_stack * list1, T_stack * list2, int j){
	int i;
	
	printf("exp: [size=%2d] ", list1->sp);
	for(i = 0 ; i < list1->sp; i++){
		
		if( (list1->data[i]).status == 'O' )
			printf("[  %c]",  (list1->data[i]).value);
		
		else
			printf("[%3d]",  (list1->data[i]).value);
				
	}
		
			
	for(i = list1->sp; i < list1->nbMaxElt; i++)
		printf("[   ]");
		
	printf(" | ");
	printf("num: [size=%2d] ", list2->sp);
	for(i = 0 ; i < list2->sp; i++){
		
		if( (list1->data[i]).status == 'O' )
			printf("[  %c]",  (list1->data[i]).value);
		
		else
			printf("[%3d]",  (list1->data[i]).value);
	}
			
	for(i = list2->sp; i < list2->nbMaxElt; i++)
		printf("[   ]");

	printf("[ %d ]\n", j);
}



