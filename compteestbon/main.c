#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include "elt.h"
#include "search.h"

int main(int argc, char * argv[]) {

	T_stack exp = newStack(12);
	T_stack num = newStack(12);
	T_stack best = newStack(12);
	T_stack * p_best = &best;
		
	T_elt plus  = {'+','O'};
	T_elt minus = {'-','O'};
	T_elt times = {'x','O'};
	T_elt div   = {'/','O'};
	push(plus, &num); push(minus, &num); push(times, &num); push(div, &num); 

	int cont;
	int res;
  	for(cont=1; cont < argc; cont++){
		if(cont==(argc-1)){
			res=atoi(argv[cont]);
		}else{
			T_elt x = {atoi(argv[cont]),'V'};
			push(x, &num);
		}
	}

	best = search(&exp, &num, res, p_best);
	show_operations(&best, compute(best).value);
	
	return 0;
}
