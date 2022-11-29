#include "elt.h"

#define STACK_NBMAX_ELT 20	

/////////////////////////////////////////////////////////////////////////
// CHOISIR ICI L'IMPLEMENTATION DES PILES 
/////////////////////////////////////////////////////////////////////////

//#define IMPLEMENTATION_STATIC_CONTIGUOUS
//#define IMPLEMENTATION_DYNAMIC_CONTIGUOUS
//#define IMPLEMENTATION_DYNAMIC_LINKED

#ifdef  IMPLEMENTATION_STATIC_CONTIGUOUS

typedef struct {
	int sp; 
	int nbMaxElt;
	T_elt data[STACK_NBMAX_ELT];
	int no_operations;
	int no_integers;
} T_stack;

void showStack (const T_stack * p);
void emptyStack (T_stack *p);
T_stack newStack(int size);
T_stack exampleStack(int n);
T_elt pop(T_stack *p);
T_elt top(const T_stack *p);
void push(T_elt e, T_stack *p);
int isEmpty (const T_stack * p);

#endif