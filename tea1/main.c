#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "elt.h"
#include "stack_cs.h"

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

T_elt rpn_eval(char * exp){
    T_list lis = s2list(exp);
    //showList(lis);
    T_stack pilha = newStack();
    while(lis != NULL) {
        push(lis->data,&pilha);
		lis = lis->pNext; 
	}
    int num1=0, num2=0;
    int acumulo=0;
    char status = RESULT;
    while(!isEmpty(&pilha)){
        T_elt t1 = pop(&pilha);
        if(t1.status!=OPERATOR){
            num2=num1;
            num1=t1.value;
            acumulo+=1;
            if(acumulo>=3){
                status=VALID;
            }
        }else{
            if(t1.value==43){
                num1=num1+num2;
            }
            if(t1.value==42){
                num1=num1*num2;
            }
            if(t1.value==45){
                if(num2-num1<0){
                    status=INVALID;
                }
                num1=num2-num1;
            }
            if(t1.value==47){
                if(num2%num1!=0){
                    status=INVALID;
                }
                num1=num2/num1;
            }
            acumulo=0;
        }
    }
    T_elt retorno = genElt();
    retorno.status=status;
    retorno.value=num1;
    return retorno;
}

int main(){
    //T_list lis = s2list("12 6 + 5 +");
    //showList(lis);
    //printf("%s\n",toString(getFirstElt(lis)));
    T_elt retorno = rpn_eval("5 10 2 /");
    printf("%s\n",toString(retorno));
    return 0;
}