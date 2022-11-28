#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

//#define CLEAR2CONTINUE
//#include "../include/traces.h" 

// C'est dans le fichier elt.h qu'on doit choisir l'implémentation des T_elt
#include "elt.h"	//T_elt

// implémentation des piles contigüe dynamique
#include "stack_cd.h"

void show2lists(T_stack * list1, T_stack * list2, int j);
void show1list(T_stack * list1, int res);

void put_botton(T_stack *list1, T_elt element){
	int i, tam = list1->sp;
	T_stack list2 = newStack(15);
	
	for(i = 0 ; i < tam ; i++)push(pop(list1), &list2);
	push(element, list1);
	for(i = 0 ; i < tam ; i++)push(pop(&list2), list1);
	
	freeStack(&list2);
}

int is_valid(T_stack * exp){ //RPN_eval_stack

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

int has_op(T_stack * exp){ // 
	
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

T_elt compute(T_stack exp_){
	int i;
	int tam = exp_.sp;
	T_stack exp = newStack(15);
	T_stack exp2 = newStack(15);
	
	for (i = 0 ; i <  tam ; i++){
		push(pop(&exp_) , &exp2);
	}	
	
	for (i = 0 ; i <  tam ; i++){
		push(pop(&exp2) , &exp);
	}
	
	tam = (exp.sp)/2; // obtains the number of operators
	T_stack op = newStack(10);
	T_elt result = {0};
	// separates operators and numbers
	for (i = 0 ; i < tam ; i++){
		push(pop(&exp), &op);
	}
	
	tam = op.sp;
	// tests all operators
	for (i = 0 ; i < tam ; i++){
		T_elt num1 = pop(&exp);
		T_elt num2 = pop(&exp);
		T_elt operation = pop(&op);
		
		switch (operation.value){
		
			case '+':
				result.value = num2.value + num1.value;
				result.status = 'V';
			break;
				
			case '-':
				result.value = num2.value - num1.value;
				if( result.value > 0 )result.status = 'V';
				else result.status = 'I';
			break;
			
			case '*':
				result.value = num2.value * num1.value;
				result.status = 'V';

			break;
			
			case '/':
				result.value = num2.value / num1.value;
				if( num2.value % num1.value )result.status = 'I';
				else result.status = 'V';
			
			break;
			
			default:
				printf("ERROR!!!! switch case");	
		
		}
		push(result, &exp);
		
		if(result.status == 'I'){
			return result;
		}
		
	}
	
	freeStack(&exp2);
	freeStack(&exp);
	result.status = 'R';	
	return result;
	
}

T_stack search(T_stack * exp, T_stack * num, int target, T_stack * best){
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
					search(exp, &num_, target, best);
					
				put_botton(num, pop(exp) );
			}
		}
		else{
			push(aux, exp);
				
			if( aux.status != 'O' ){
				pop(&num_);
			}
				
			if(is_valid(exp))	
				search(exp, &num_, target, best);
				
			put_botton(num, pop(exp) );
		}
					
	}
	int aux = is_valid(exp);
	//int aux = 1;
	if(aux == 1){		
		T_elt res = compute(*exp);
		T_elt res_old = compute(*best);
		if(res.status == 'R'){
			if( abs(res.value - target) <= abs(res_old.value - target)){
				if( abs(res.value - target) == abs(res_old.value - target)){			
					if( best->sp > exp->sp ){
						//show2lists(exp, num, res.value);
						best->sp = exp->sp;
						best->nbMaxElt = exp->nbMaxElt;
						int tam = exp->sp;
						for(i = 0; i < tam ; i++){
							best->data[i] = exp->data[i];
						}										
					}
				}
				else{
					//show2lists(exp, num, res.value);
					best->sp = exp->sp;
					best->nbMaxElt = exp->nbMaxElt;
					int tam = exp->sp;
					for(i = 0; i < tam ; i++){
						best->data[i] = exp->data[i];
					}
				}	
			}
		}
	}
	
	return *best;
}


int main(int argc, char ** argv) {
	T_stack exp = newStack(12);
	T_stack num = newStack(12);
	T_stack best = newStack(12);
	T_stack * p_best = &best;
		
	T_elt plus  = {'+','O'};
	T_elt minus = {'-','O'};
	T_elt times = {'*','O'};
	T_elt div   = {'/','O'};
	T_elt one   = {  8,'V'};
	T_elt two   = {  3,'V'};
	T_elt three = {  10,'V'};
	T_elt four  = {  7,'V'};
	T_elt five  = { 4,'V'};
	T_elt six   = { 2,'V'};
	
	//push(plus, &num); push(three, &num); push(two, &num); push(one, &num);
	push(plus, &num); push(minus, &num); push(times, &num); push(div, &num); 
	push(six, &num); push(five, &num); push(four, &num); push(three, &num); push(two, &num); push(one, &num);
	
	best = search(&exp, &num, 219, p_best);
	show1list(&best, compute(best).value);
	
	return 0;
}

void show1list(T_stack * list1, int res){
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
	printf("res: [%5d] \n", res);
}

void show2lists(T_stack * list1, T_stack * list2, int res){
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

	printf(" | ");
	printf("RES: [size=%5d] \n", res);
}



