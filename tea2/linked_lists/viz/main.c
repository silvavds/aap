#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "list.h"

#define MAX_BUF 256

// dot exemple.dot -T png -o exemple.png

void generatePNG(const t_node * const_list, char * filename);

int main(){
	
	t_node * list1 = create_node(99);	
	list1 = add_node(31, list1);
	list1 = add_node(151, list1);
	list1 = add_node(11, list1);
		
	show_list(list1);
	
	generatePNG(list1, "output");

	return 0;
}

void generatePNG(const t_node * const_list, char * filename){
	char buffer[MAX_BUF] = {0};
	t_node * list = const_list;

	FILE *read;
	read = fopen("base.dot", "r");
	
	FILE *write;
	sprintf(buffer, "%s.dot", filename);
	write = fopen(buffer, "w");
	int i = 0;
	
	while(i < 20) {
		fgets(buffer, MAX_BUF, read);
    		//printf("%s \n", buffer);
    		
    		fprintf(write, "%s", buffer);
    		
    		i++;
	}
	fprintf(write, "\n \n");
	/*
	"ID_0001" [label = "{<elt> AAAAP | <next> }"];    
	"ID_0001" : next -> "ID_0002";	   	       
	*/
	i = 1;
	while(list != NULL){
		
		if(list->next != NULL){
			fprintf(write, "\"ID_%04d\" [label = \"{ %d | <next> }\"]; \n", i, list->data);
			fprintf(write, "\"ID_%04d\" : next -> \"ID_%04d\" ; \n", i, i+1);
		}
		else{
			//"ID_0006" [label = "{<elt> Programmation | <next> NULL}"];
			fprintf(write, "\"ID_%04d\" [label = \"{ %d | <next> NULL}\"]; \n", i, list->data);
		}
		i++;
		list = list->next;
	}
	fprintf(write, "}");
	

	sprintf(buffer, "dot %s.dot -T png -o %s.png", filename, filename);
	//sprintf(buffer, "pwd");
	printf("%s \n", buffer);
	//int ret = system( & buffer[0]);
	//int ret = system("#!/bin/bash -c 'dot ./output.dot -T png -o ./abcd.png");
	//int ret = system("dot output.dot -T png -o output.png");

	FILE *fp;
	char *command = "dot output.dot -T png -o output.png";
	fp = popen(command,"w"); 
	fclose(fp);
	
	
	//execv("/bin/bash", "bash", "-c", "dot output.dot -T png -o output.png", (char *) NULL);
	//printf("%d \n", ret);
}
