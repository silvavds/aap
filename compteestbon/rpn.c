#include "rpn.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

T_elt createElt(char * current){
    T_elt current_elt;
    if(current[0]=='+'||current[0]=='-'||current[0]=='*'||current[0]=='/'){
        current_elt.status=OPERATOR;
        current_elt.value=current[0];
    }else{
        current_elt.status=RESULT;
        current_elt.value=atoi(current);
    }
    return current_elt;
}

T_list s2list(char * exp){
    T_node * lista = {NULL};
    char * current = calloc(4, sizeof(char));
    int j=0;
    // Espaco 32
    for(int i=0;i<strlen(exp);i++){
        if((int)exp[i]!=32){
            current[j]=exp[i];
            j++;
        }else{
            lista = addNode(createElt(current), lista);
            j=0;
            free(current);
            current=calloc(3, sizeof(char));
        }
    }
    lista = addNode(createElt(current), lista);
    free(current);
    return lista;
}

T_elt rpn_calculate(T_stack * pilha){
    T_stack pilha_eval = newStack(20);
    int num1=0, num2=0, res=0;
    char status = RESULT;
    while(!isEmpty(pilha)){
        T_elt t1 = pop(pilha);
        if(t1.status!=OPERATOR){
            push(t1, &pilha_eval);
        }else{
            if(t1.value=='+'){
                num1=pop(&pilha_eval).value;
                num2=pop(&pilha_eval).value;
                res=num1+num2;
                T_elt t2 = genElt();
                t2.status=RESULT;
                t2.value=res;
                push(t2,&pilha_eval);
            }
            if(t1.value=='*'){
                num1=pop(&pilha_eval).value;
                num2=pop(&pilha_eval).value;
                res=num1*num2;
                T_elt t2 = genElt();
                t2.status=RESULT;
                t2.value=res;
                push(t2,&pilha_eval);
            }
            if(t1.value=='-'){
                num1=pop(&pilha_eval).value;
                num2=pop(&pilha_eval).value;
                if(num2-num1<0){
                    status=INVALID;
                }
                res=num2-num1;
                T_elt t2 = genElt();
                t2.status=status;
                t2.value=res;
                push(t2,&pilha_eval);
            }
            if(t1.value=='/'){
                num1=pop(&pilha_eval).value;
                num2=pop(&pilha_eval).value;
                if(num2%num1!=0){
                    status=INVALID;
                }
                res=(int)(num2/num1);
                T_elt t2 = genElt();
                t2.status=status;
                t2.value=res;
                push(t2,&pilha_eval);
            }
        }
    }
    T_elt retorno = pop(&pilha_eval);
    if(retorno.status!=INVALID){
        if(isEmpty(&pilha_eval)){
            retorno.status=RESULT;
        }else{
            retorno.status=VALID;
        }
    }
    return retorno;
}

T_elt rpn_eval_stack(T_stack * exp){
    T_stack pilha = newStack(20);
    while(!isEmpty(exp)) {
        T_elt e = pop(exp);
        push(e,&pilha);
	}
    T_elt retorno = rpn_calculate(&pilha);
    return retorno;
}

T_elt rpn_eval(char * exp){
    T_list lis = s2list(exp);
    T_stack pilha = newStack(20);
    while(lis != NULL) {
        push(lis->data,&pilha);
		lis = lis->pNext; 
	}
    T_elt retorno = rpn_calculate(&pilha);
    return retorno;
}