#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h> 
// ceil, floor : #include <math.h>

#include "test_utils.h"
#include "traces.h" 
#include "check.h" 
#include "elt.h"
#include <time.h>

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

#define MINIMIER_TAS

#ifndef MINIMIER_TAS
#define MAXIMIER_TAS
#endif

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

T_elt * heapSort(T_elt * d, int n);
T_elt * quickSort(T_elt * number,int first,int last);
void merge(T_elt * arr, int l, int m, int r);
T_elt * mergeSort(T_elt * arr, int l, int r);
 
void runTimeTests(){
	printf("n,heap,quick,merge\n");
	int incremento=10;
	for(int sz=10;sz<50000;sz+=incremento){
		if(sz>100&&incremento==10){
			incremento=100;
		}
		if(sz>1000&&incremento==100){
			incremento=1000;
		}
		T_elt * randHeap = (T_elt*)malloc(sz*sizeof(T_elt));
		T_elt * randQuick = (T_elt*)malloc(sz*sizeof(T_elt));
		T_elt * randMerge = (T_elt*)malloc(sz*sizeof(T_elt));
		int num;
		for(int i=0;i<sz;i++){
			num=1+rand()%100;   //Generate number between 0 to 99
			randHeap[i]=num;
			randQuick[i]=num;
			randMerge[i]=num;
		}
		clock_t begin = clock();
		T_elt * sorted = heapSort(randHeap,sz);
		clock_t end = clock();
		double time_spent_heap = (double)(end - begin) / CLOCKS_PER_SEC;

		begin = clock();
		T_elt * sorted2 = quickSort(randQuick,0,sz-1);
		end = clock();
		double time_spent_quick = (double)(end - begin) / CLOCKS_PER_SEC;

		begin = clock();
		T_elt * sorted3 = mergeSort(randMerge,0,sz-1);
		end = clock();
		double time_spent_merge = (double)(end - begin) / CLOCKS_PER_SEC;

		printf("%d,%.8f,%.8f,%.8f\n",sz,time_spent_heap,time_spent_quick,time_spent_merge);
	}
}

int main(void) {
	runTimeTests();

	// int ex1[] = { 18, 15, 11, 10, 15, 6, 1, 7, 4, 9};   // 10
	// int ex2[] = { 18, 16, 11, 10, 15, 6, 1, 7, 4, 9, 3}; // 11
	// int ex3[] = { 3, 1, 8, 5, 9, 6, 11, 7, 4, 12}; // 10
	// int ex4[] = { 7, 15, 1, 9, 15, 10, 11, 4, 18, 6 }; //10 
	// int ex5[] = { 7, 15, 1, 9, 15, 10, 11, 4, 18, 6 }; //10 
	// int ex6[] = { 7, 15, 1, 9, 15, 10, 11, 4, 18, 6 }; //10 
	
	// T_heap * maximier;
	// T_elt e1;

	// maximier = initHeap(ex4, 10);
	// buildHeapV1(maximier); 
	// showHeap(maximier);
	
	// free(maximier);
	// maximier = initHeap(ex4, 10);
	// buildHeapV2(maximier);
	// showHeap(maximier);

	// T_elt * sorted = heapSort(ex4,10);
	// for(int i=0;i<10;i++){
	// 	printf("%d ",sorted[i]);
	// }
	// printf("\n");

	// T_elt * sorted2 = quickSort(ex5,0,9);
	// for(int i=0;i<10;i++){
	// 	printf("%d ",sorted2[i]);
	// }
	// printf("\n");

	// T_elt * sorted3 = mergeSort(ex6,0,9);
	// for(int i=0;i<10;i++){
	// 	printf("%d ",sorted3[i]);
	// }
	// printf("\n");
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
    T_elt pAux;
    pAux = p->tree[i];
    p->tree[i] = p->tree[j];
    p->tree[j] = pAux;
}

void siftUp(T_heap *p, int k) {
    int i = iPARENT(k);
	if(i<0){
		return;
	}
	#ifdef MAXIMIER_TAS
    while(p->tree[i]<p->tree[k]){
		swap(p,i,k);
		k=i;
		i = iPARENT(i);
		if(i<0){
			return;
		}
	}	
	#endif
	#ifdef MINIMIER_TAS
    while(p->tree[i]>p->tree[k]){
		swap(p,i,k);
		k=i;
		i = iPARENT(i);
		if(i<0){
			return;
		}
	}	
	#endif
}

void addElt(T_heap *p, T_elt e) {
    p->tree[p->nbElt] = e;
    p->nbElt++;
    buildHeapV1(p);
}

void buildHeapV1(T_heap * p){
	#ifdef MAXIMIER_TAS
	for(int i=1;i<p->nbElt;i++){
		siftUp(p,i);
	}
	#endif
	#ifdef MINIMIER_TAS
	for(int i=(p->nbElt-1);i>=0;i--){
		siftUp(p,i);
	}
	#endif
}

void siftDown(T_heap *p, int k) {
	int i;
	#ifdef MAXIMIER_TAS
	while(k<p->nbElt){
		i = iLCHILD(k);
		if(p->tree[iRCHILD(k)]>p->tree[i]){
			i = iRCHILD(k);
		}
		if(i>=p->nbElt){
			return;
		}
		if(p->tree[k]>=p->tree[i]){
			return;
		}else{
			swap(p,i,k);
			k=i;
		}
	}
	#endif
	#ifdef MINIMIER_TAS
	while(k<p->nbElt){
		i = iLCHILD(k);
		if(p->tree[iRCHILD(k)]<p->tree[i]&&iRCHILD(k)<p->nbElt){
			i = iRCHILD(k);
		}
		if(i>=p->nbElt){
			return;
		}
		if(p->tree[k]<=p->tree[i]){
			return;
		}else{
			swap(p,i,k);
			k=i;
		}
	}
	#endif
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
	#ifdef MAXIMIER_TAS
	for(int i=floor(p->nbElt/2)-1;i>=0;i--){
		siftDown(p,i);
	}
	#endif
	#ifdef MINIMIER_TAS
	for(int i=floor(p->nbElt/2)-1;i>=0;i--){
		siftDown(p,i);
	}
	#endif
}

T_elt * heapSort(T_elt * d, int n){
	T_heap * heap;
	heap = initHeap(d, n);
	buildHeapV1(heap);
	T_elt * sorted = (T_elt*)malloc(n*sizeof(T_elt));
	T_elt e;
	for(int i=0;i<n;i++){
		e=removeMax(heap);
		sorted[i]=e;
	}
	return sorted;
}

T_elt * quickSort(T_elt * number,int first,int last){
	int i, j, pivot, temp;
	if(first<last){
		pivot=first;
		i=first;
		j=last;
		while(i<j){
			while(number[i]<=number[pivot]&&i<last){
				i++;
			}
			while(number[j]>number[pivot]){
				j--;
			}
			if(i<j){
				temp=number[i];
				number[i]=number[j];
				number[j]=temp;
			}
		}
		temp=number[pivot];
		number[pivot]=number[j];
		number[j]=temp;
		quickSort(number,first,j-1);
		quickSort(number,j+1,last);
	}
	return number;
}

void merge(T_elt * arr, int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
 
    /* create temp arrays */
    int L[n1], R[n2];
 
    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
 
    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
 
    /* Copy the remaining elements of L[], if there
    are any */
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
	
    /* Copy the remaining elements of R[], if there
    are any */
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}
 
/* l is for left index and r is right index of the
sub-array of arr to be sorted */
T_elt * mergeSort(T_elt * arr, int l, int r){
    if (l < r) {
        // Same as (l+r)/2, but avoids overflow for
        // large l and h
        int m = l + (r - l) / 2;
 
        // Sort first and second halves
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
 
        merge(arr, l, m, r);
    }
	return arr;
}