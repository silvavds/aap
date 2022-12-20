#include <string.h>
#include <stdio.h>
#include "test_utils.h"

// TODO : placer les compteurs aux endroits appropriés :
// stats.nbOperations ++;
// stats.nbComparisons ++;

void fusionner(T_elt t [], int start, int half, int end); 

T_data fusionSort(T_data start, int n) {

	int half = n/2;
	T_elt * A = start.pElt;

	if(n==1){
	stats.nbComparisons++;
	return start;
	}
	
	T_data leftPart= fusionSort(start, half);
	T_data rightPart = fusionSort(genData(0,&(A[half])), (n-half));
	
	fusionner(A, 0, half-1, n-1);
	
	return genData(0, A);

}

void fusionner(T_elt t [], int start, int half, int end) {
	T_elt aux[end - start + 1]; // !! Allocation dynamique sur la pile (standard C99) 
	int i = 0, j = half - start + 1, k = 0;

	memcpy(aux, &t[start], (end - start + 1) * sizeof(T_elt));	// Copie des données à fusionner
	stats.nbOperations += (end - start + 1);

	while (i <= half - start && j <= end - start){
		stats.nbComparisons +=2;
		if (aux[i] <= aux[j]){
			stats.nbComparisons ++;
			t[start + k++] = aux[i++];	// aux[i] est plus petit : on le place dans t
			stats.nbOperations ++;
		}
		else{
	 		t[start + k++] = aux[j++];	// aux[j] est plus petit : on le place dans t
	 		stats.nbOperations ++; 
		}
	}
	for (; i <= half - start; t[start + k++] = aux[i++]); // le reste du tableau gauche
		stats.nbComparisons ++;
	for (; j <= end - start; t[start + k++] = aux[j++]); // le reste du tableau droit
		stats.nbComparisons ++;
}



