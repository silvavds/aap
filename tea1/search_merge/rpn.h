#include <stdio.h>
#include "elt.h"
#include "list.h"

//#define IMPLEMENTATION_STATIC_CONTIGUOUS
//#define IMPLEMENTATION_DYNAMIC_CONTIGUOUS
#define IMPLEMENTATION_DYNAMIC_LINKED

#ifdef IMPLEMENTATION_STATIC_CONTIGUOUS
#include "stack_cs.h"
#endif

#ifdef IMPLEMENTATION_DYNAMIC_CONTIGUOUS
#include "stack_cd.h"
#endif

#ifdef IMPLEMENTATION_DYNAMIC_LINKED
#include "stack_cld.h"
#endif

T_list s2list(char * exp);
T_elt rpn_eval(char * exp);
int numberOfOperators(T_stack * stack);
int numberOfNumbers(T_stack * stack);