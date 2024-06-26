#include <assert.h> // assert

//#define DEBUG
#include "../include/check.h" 

//#define CLEAR2CONTINUE
#include "../include/traces.h" 

#include "stack_cd.h" // type et protypes liés à T_stack

#ifdef IMPLEMENTATION_DYNAMIC_CONTIGUOUS
#define STACK_THRESHOLD 1024

/*
typedef struct {
	int sp; 
	int nbMaxElt;
	T_elt * data;
} T_stack;
*/

T_stack newStack(int size) {
	// Opération permettant d'allouer la mémoire pour une pile dynamique
	T_stack s;
	//TOUCH_HERE("Ben là, c'est à vous ! \n"); 
	//printf("Allocation \n");
	CHECK_IF(s.data = (T_elt *)malloc( sizeof(T_elt)*size ), NULL, "malloc newStack");	// traces.h
	s.nbMaxElt = size;
	s.sp = 0;
	
	return s; 
}

void freeStack (T_stack *p) {
	// Libère la pile en désallouant la mémoire
	//TOUCH_HERE("Ben là, c'est à vous ! \n");
	p->sp = 0;
	p-> nbMaxElt = 0;
	free(p->data);
	p->data = NULL;
	//printf("De-Allocation \n");
}

void push(T_elt e, T_stack *p) {
	// Opération consistant à empiler un élément T 
	// sur la pile modifiant ainsi son état
	// Prévoir des seuils d’agrandissement 
	// pour éviter des realloc systématiques
	// seuil = STACK_THRESHOLD
	//TOUCH_HERE("Ben là, c'est à vous ! \n");
	
	// if there is NO space
	if( p->sp == p->nbMaxElt ){
		printf("Allocation necessaire! \n");
		CHECK_IF(p->data = realloc(p->data, (p->nbMaxElt+STACK_THRESHOLD)*sizeof(T_elt)), NULL, "realloc newString");
		p->nbMaxElt += STACK_THRESHOLD;
	}
	
	p->data[p->sp++] = e; // *(p->data+p->sp)=e; p->sp++;
}

// A Adapter (déjà fait) ///////////////////////////////////////////////////////////////

T_stack exampleStack(int n) {
	// Renvoie une nouvelle pile d'exemple, contenant n éléments
	int i; 
	T_stack s;

	// Cas de l'implémentation contigüe statique
	// assert(n<=STACK_NBMAX_ELT); 
	// s = newStack(); 

	// Adaptation: la fonction newStack prend maintenant un paramètre
	s = newStack(n); // Cas de l'implémentation contigüe dynamique 
	
	for(i=0;i<n;i++) {
		push(genElt(),&s); 
	}

	return s;
}

// RIEN NE CHANGE //////////////////////////////////////////////////////////////////////

void showStack (const T_stack * p) {
	int i; 
	// Produire une fonction d’affichage de la pile
	// On affiche en commençant par le sommet de la pile 

	if (p->sp == 0) {
		printf("Pile vide !"); // pile vide ! 
		return;
	}
 	
	printf("Sp = %5d [",p->sp);
	for(i=p->sp-1;i>=0; i--) {
		printf("%s] [", toString(p->data[i]));
	}
	printf("$]");
}

T_elt pop(T_stack *p) {
	// Cette opération extrait de la pile, l’élément au sommet, 
	// modifiant ainsi son état
	assert(p != NULL); 
	assert(p->sp > 0); 
	return p->data[--p->sp]; 
	// D'abord on décrémente, puis on regarde ce qui se trouve à cet endroit... 
	// C'est ce que l'on renvoie
}

T_elt top(const T_stack *p) {
	// Cette opération permet d’accéder à l’élément en sommet de pile
	assert(p != NULL);
	assert(p->sp > 0);
	return p->data[p->sp-1];
}

void emptyStack (T_stack *p) {
	// Vide la pile 
	p->sp = 0; 
}

int isEmpty (const T_stack * p) {
	// Cette opération permet de tester si la pile est vide.
	assert(p!=NULL);
	if (p->sp == 0) return 1; 
	else return 0;
	
}

#endif


