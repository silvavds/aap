#include <stdio.h>
#include <string.h>
#include <assert.h>

//#define CLEAR2CONTINUE
#include "../include/traces.h" 

// C'est dans le fichier elt.h qu'on doit choisir l'implémentation des T_elt
#include "elt.h"	//T_elt

// implémentation des piles contigüe dynamique
#include "stack_cd.h"

void show2lists(T_stack * list1, T_stack * list2, int j);

void put_botton(T_stack *list1, int element){
	int i, tam = list1->sp;
	T_stack list2 = newStack(15);
	
	for(i = 0 ; i < tam ; i++)push(pop(list1), &list2);
	push(element, list1);
	for(i = 0 ; i < tam ; i++)push(pop(&list2), list1);
	
	freeStack(&list2);
}

int is_valid(T_stack * exp){

	int i, aux, opr=0, num=0;	
	T_stack exp2 = *exp;
	int tam = exp2.sp;
	
	for(i = 0 ; i < tam ; i++){
	
		aux = pop(&exp2);
	
		if(aux == '+' || aux == '-' || aux == '*' || aux == '/')opr++;
		else num++;
	}
	
	if(num > opr)return (num - opr);
	
	else return 0;
	
}

int has_op(T_stack * exp){
	
	int i, aux;
	int tam = exp->sp;
	
	T_stack exp2 = *exp;
	
	for(i = 0 ; i < tam ; i++){
		aux = pop(&exp2);
		if(aux == '+' || aux == '-' || aux == '*' || aux == '/')
			return 1;
	}
		
	return 0;
}

int search(T_stack * exp, T_stack * num, int * res){
	int i;

	//show2lists(&exp, &num, 0);
	
	// tests all possible (num+ops) only a single time
	for(i = 0 ; i < num->sp ; i++){					
			
		T_stack num_ = *num;
		int aux = pop(num); 
		
		if( has_op(exp) ){
			
			if(aux != '+' && aux != '-' && aux != '*' && aux != '/'){
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
				
			if(aux != '+' && aux != '-' && aux != '*' && aux != '/'){
				pop(&num_);
			}
				
			if(is_valid(exp))	
				search(exp, &num_);
				
			put_botton(num, pop(exp) );
		}
					
	}
	int aux = is_valid(exp);
	//int aux = 1;
	//if(aux == 1)show2lists(exp, num, i);		
	
	return 0;
}


int main(int argc, char ** argv) {
	T_stack exp = newStack(12);
	T_stack num = newStack(12);
	
	int * res = (int *)malloc(sizeof(int));
	
	push('/', &num); push('*', &num); push('-', &num); push('+', &num); push(6, &num); push(5, &num); push(4, &num); push(3, &num); push(2, &num); push(1, &num);
	//push('+', &num); push(3, &num); push(2, &num); push(1, &num);
	
	search(&exp, &num, res);

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



