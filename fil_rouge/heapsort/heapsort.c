#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h> 
// ceil, floor : #include <math.h>


#include "traces.h" 
#include "check.h" 
#include "elt.h"

#define HEAP_ALLOCATION_OFFSET 5

typedef struct {
	unsigned int nbElt;
	unsigned int nbMaxElt;
	T_elt * tree;	
} T_heap;

#define iPARENT(i) 			(i-1)/2
#define iLCHILD(i) 			(2*i)+1
#define iRCHILD(i) 			(2*i)+2
#define iLASTINTERNAL(n)	n/2 -1
#define isINTERNAL(i,n) 	(2*i<(n-1))
#define isLEAF(i,n) 			(2*i>=(n-1))
#define isINTREE(i,n)		(i<n)
#define isROOT(i)				(i==0)
#define nbINTERNALS(n) 		n/2
#define nbLEAVES(n) 			ceil((double)n/2)
#define VALP(pHeap, i)		pHeap->tree[i]		
#define VAL(heap, i)			heap.tree[i]		

//TOUCH_HERE("Ben là, c'est à vous ! \n");

#define MINIMIER_TAS

T_heap * newHeap(unsigned int nbMaxElt);
void freeHeap(T_heap *p); 
T_heap * initHeap(T_elt t[], int n) ;
void showHeap(T_heap *p);
void showHeap_rec(T_heap *p, int root, int indent); 

void swap(T_heap *p, int i, int j);
void siftUp(T_heap *p, int k);
void addElt(T_heap *p, T_elt e);
void buildHeapV1(T_heap * p);

void siftDown(T_heap *p, int k);
T_elt getMax(const T_heap *p);
T_elt removeMax(T_heap *p);
void buildHeapV2(T_heap * p); 
 

int main(void) {

    // T_elt ex[] = {3,2,1};
	// T_elt e2 = 5;
	//T_heap * maximier = initHeap(ex,3);
    // showHeap(maximier);
	// addElt(maximier,e2);
	// printf("------------------------------------\n");
	// showHeap(maximier);
	// printf("------------------------------------\n");
	
	int ex1[] = { 18, 15, 11, 10, 15, 6, 1, 7, 4, 9};   // 10
	int ex2[] = { 18, 16, 11, 10, 15, 6, 1, 7, 4, 9, 3}; // 11
	int ex3[] = { 3, 1, 8, 5, 9, 6, 11, 7, 4, 12, 0}; // 10
	int ex4[] = { 7, 15, 1, 9, 15, 10, 11, 4, 18, 6 }; //10 
	
	// T_heap * max2 = initHeap(ex3,10);
    // showHeap(max2);
	// buildHeapV2(max2);
	// showHeap(max2);

	// removeMax(max2);
	// printf("------------------------------------\n");
	// showHeap(max2);

	// //TOUCH_HERE("Ben là, c'est à vous ! \n");
	T_heap * maximier;
	T_elt e1;

	// allocation et l'initialisation d'un tas à partir d'un tableau 
	maximier = initHeap(ex1, 10);
	showHeap(maximier);
	
	// ajouter elt, remonter
	addElt(maximier, 16);
	showHeap(maximier);
	
	// création d'un maximier V1
	free(maximier);
	maximier = initHeap(ex4, 10);
	showHeap(maximier);
	buildHeapV1(maximier); 
	showHeap(maximier);
	
	// getMax
	free(maximier);
	maximier = initHeap(ex2, 11);
	showHeap(maximier);
	e1 = getMax(maximier);
	printf("max : %s\n", toString(e1));
	
	// suppression element, redescendre
	e1 = removeMax(maximier);
	printf("max : %s\n", toString(e1));
	showHeap(maximier);
	
	// création d'un maximier V2 
	free(maximier);
	maximier = initHeap(ex3, 10);
	showHeap(maximier);
	buildHeapV2(maximier);
	showHeap(maximier);

}


// Déjà écrit //////////////////////////////////////////////////
void showHeap(T_heap *p) {
	printf("Affichage du tas (nbElt : %d)\n",p->nbElt);
	showHeap_rec(p,0,0); 
}

void showHeap_rec(T_heap *p, int root, int indent) {
	// affiche récursivement en mode pseudo graphique 
	// ordre de récurrence  : taille du sous-arbre 
	int i; 
	
	if (! isINTREE(root,p->nbElt)) return;  
	
	showHeap_rec(p, iRCHILD(root), indent+1);
	for(i=0;i<indent;i++) {
		printf("\t"); 
	}
    T_elt res = VALP(p,root);
	printf("%s(i:%d)\n",toString(res), root);
	showHeap_rec(p, iLCHILD(root), indent+1);
}

// Déjà écrit //////////////////////////////////////////////////


T_heap * newHeap(unsigned int nbMaxElt){

	T_heap * pAux = (T_heap*)malloc(sizeof(T_heap));
    pAux->tree = (T_elt*) malloc(nbMaxElt*sizeof(T_elt));
    pAux->nbElt = 0;
    pAux->nbMaxElt = nbMaxElt;

	return pAux; 

}

void freeHeap(T_heap *p) {
    free(p->tree);
    free(p);
}


T_heap * initHeap(T_elt t[], int n) {
	T_heap *pAux = newHeap(n + HEAP_ALLOCATION_OFFSET); 
    for(int i=0;i<n;i++){
        pAux->tree[i]=t[i];
    }
    pAux->nbElt=n;
	return pAux; 
}

void swap(T_heap *p, int i, int j) {
    T_elt * pAux;
    pAux = p->tree[i];
    p->tree[i] = p->tree[j];
    p->tree[j] = pAux;
}

void siftUp(T_heap *p, int k) {
    int i = iPARENT(k);
    while(p->tree[i]<p->tree[k]){
		swap(p,i,k);
		k=i;
		i = iPARENT(i);
	}	
}

void addElt(T_heap *p, T_elt e) {
    p->tree[p->nbElt] = e;
    p->nbElt++;
    buildHeapV1(p);
}

void buildHeapV1(T_heap * p){
	for(int i=1;i<p->nbElt;i++){
		siftUp(p,i);
	}
	
}

void siftDown(T_heap *p, int k) {
	int i;
	while(k<p->nbElt){
		i = iLCHILD(k);
		if(p->tree[iRCHILD(k)]>p->tree[i]){
			i = iRCHILD(k);
		}
		if(p->tree[k]>=p->tree[i]){
			return;
		}else{
			swap(p,i,k);
			k=i;
		}
	}
}

T_elt getMax(const T_heap *p){
    T_elt aux;
    aux = p->tree[0];
	return aux; 
}


T_elt removeMax(T_heap *p) {
	T_elt aux; 
	aux = getMax(p);
    swap(p,0,p->nbElt-1);
	p->nbElt--;
	buildHeapV1(p);
	return aux; 
}


void buildHeapV2(T_heap * p){
	for(int i=floor(p->nbElt/2)-1;i>=0;i--){
		siftDown(p,i);
	}
}