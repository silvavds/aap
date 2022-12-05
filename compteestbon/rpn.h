#include <stdio.h>
#include "elt.h"
#include "list.h"

#ifndef _RPN_H_
#define _RPN_H_

/////////////////////////////////////////////////////////////////////////
// CHOISIR ICI L'IMPLEMENTATION DES PILES 
/////////////////////////////////////////////////////////////////////////

#define IMPLEMENTATION_STATIC_CONTIGUOUS
//#define IMPLEMENTATION_DYNAMIC_CONTIGUOUS
//#define IMPLEMENTATION_DYNAMIC_LINKED

/*
#ifdef IMPLEMENTATION_STATIC_CONTIGUOUS
#include "stack_cs.h"
#endif

#ifdef IMPLEMENTATION_DYNAMIC_CONTIGUOUS
#include "stack_cd.h"
#endif

#ifdef IMPLEMENTATION_DYNAMIC_LINKED
#include "stack_cld.h"
#endif
*/

#include "stack_cs.h"
#include "stack_cd.h"
#include "stack_cld.h"

T_list s2list(char * exp);
T_elt rpn_calculate(T_stack * pilha);
T_elt rpn_eval_stack(T_stack * exp);
T_elt rpn_eval(char * exp);


#endif
