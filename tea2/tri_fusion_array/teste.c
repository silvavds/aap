#include <stdio.h>
#include <stdlib.h>

#include "test_utils.h"
#include "tri_fusion.h"


int main() {

	int i, j, aux=0;

	T_elt vec[MAX_ELT] = {0};
	
	printf("-------------------------------------\n");
	printf("Taille\tNb. compar\t nb oper\n");
	printf("-------------------------------------\n");
	
	for(i=MAX_ELT/100;i<MAX_ELT;i+=MAX_ELT/100){
		for(j=0;j<i;j++){
			vec[j] = rand()%1000;
		}
		
		tri_fusion(vec, 0, i);
		
		for(j = aux;j < i;j += MAX_ELT/100){
			printf("%d \t %d \t %d \n", i, stats.nbComparisons, stats.nbOperations);
			aux = i;
			stats.nbComparisons = 0;
			stats.nbOperations = 0;
				
		}
	}
	for(j=0;j<i;j++){
		vec[j] = rand()%1000;
	}
	
	tri_fusion(vec, 0, i);
	printf("%d \t %d \t %d \n", i, stats.nbComparisons, stats.nbOperations);
}
