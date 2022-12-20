#include <string.h>
#include <stdio.h>
#include "test_utils.h"

// TODO : placer les compteurs aux endroits appropriés :
// stats.nbOperations ++;
// stats.nbComparisons ++;

void tri_fusion(T_elt t [], int debut, int fin) {

	int milieu;
	
	if (debut < fin){
		stats.nbComparisons ++;
		milieu = (debut + fin)/2;
		stats.nbOperations ++;
		tri_fusion(t, debut, milieu);
		tri_fusion(t, milieu + 1, fin);
		fusionner(t, debut, milieu, fin);
	}
}

void fusionner1(T_elt t [], int d, int m, int f) {

	T_elt aux[f - d + 1]; // !! Allocation dynamique sur la pile (standard C99)
	int i, j, k;
	
	memcpy(aux, &t[d], (f - d + 1) * sizeof(T_elt)); // Copie des données à fusionner
	
	i = 0; j = m - d + 1; k = 0;
	while (i <= m - d && j <= f - d) {
		stats.nbComparisons +=2;
		stats.nbOperations ++;
		if (aux[i] <= aux[j]) {
		stats.nbComparisons ++;
		t[d + k++] = aux[i++]; // aux[i] est plus petit : on le place dans t
		stats.nbOperations ++;
		}
		else {
		t[d + k++] = aux[j++]; // aux[j] est plus petit : on le place dans t
		stats.nbOperations ++;
		}
	}
	for (; i <= m - d; t[d + k++] = aux[i++]){ // le reste du tableau gauche
		stats.nbOperations ++;
		stats.nbComparisons ++;
	}
	for (; j <= f - d; t[d + k++] = aux[j++]){ // le reste du tableau droit
		stats.nbOperations ++;
		stats.nbComparisons ++;
	}
}
