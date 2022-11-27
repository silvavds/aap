#include "rpn.h"

T_list s2list(char * exp){
    // Converte expressao em linked list de T_elt (RPN_ELT)
}

T_elt rpn_eval(char * exp){
    // Converte expressao usando a anterior
    // Avalia a expressao da lista
    // Implementa aqui a pilha
}

int numberOfOperators(T_stack * stack){
    #ifdef IMPLEMENTATION_STATIC_CONTIGUOUS
    return stack->no_operators;
    #endif

    #ifdef IMPLEMENTATION_DYNAMIC_CONTIGUOUS
    return stack->no_operators;
    #endif

    #ifdef IMPLEMENTATION_DYNAMIC_LINKED
    // Implementar dps
    #endif
}

int numberOfNumbers(T_stack * stack){
    #ifdef IMPLEMENTATION_STATIC_CONTIGUOUS
    return (stack->sp)-numberOfOperators(stack);
    #endif

    #ifdef IMPLEMENTATION_DYNAMIC_CONTIGUOUS
    return (stack->sp)-numberOfOperators(stack);
    #endif

    #ifdef IMPLEMENTATION_DYNAMIC_LINKED
    // Implementar dps
    #endif
}

char * stackToString(T_stack * stack){

}