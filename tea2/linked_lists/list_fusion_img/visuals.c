#include "visuals.h"

#define MAX_BUF 256

// dot exemple.dot -T png -o exemple.png

char * description ( t_node * const_list  ){
	int i;
	char * buffer = (char *)malloc(sizeof(char)*MAX_BUF);
	char aux[MAX_BUF] = {0};	
		
	t_node * list = const_list;	
	
	for(i = 0; i < MAX_BUF ; i++)buffer[i] = 0;
		
	while(list != NULL){
    		sprintf(aux, "%d-", list->data);
   		strcat(buffer, aux);
  		//printf("%d %s\n", list->data, buffer);
    		i++;
    		list = list->next;
	}
	
	sprintf(aux, "NULL");
	strcat(buffer, aux);
	
	return buffer;
}

void generatePNG(const t_node * const_list, char * filename){
	
	static int j = 0; 
	
	char buffer[MAX_BUF] = {0};
	t_node * list = const_list;

	FILE *read;
	read = fopen("base.dot", "r");
	
	FILE *write;
	sprintf(buffer, "./dots/%05d-%s.dot", j, filename);
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
	
	fclose(read);
	fclose(write);	

	//sprintf(buffer, "dot %s.dot -T png -o %s.png", filename, filename);
	//sprintf(buffer, "pwd");
	//printf("%s \n", buffer);
	//int ret = system( & buffer[0]);
	//int ret = system("#!/bin/bash -c 'dot ./output.dot -T png -o ./abcd.png");
	//int ret = system("dot output.dot -T png -o output.png");

	//char *command = "/bin/bash | dot output.dot -T png -o output.png";
	//FILE *fp;
	//char *command = "pwd";
	//fp = popen(command, "w"); 
	//fclose(fp);
		
	//execv("/bin/bash", "bash", "-c", "dot output.dot -T png -o output.png", (char *) NULL);
	//printf("%d \n", ret);
	j++;
}





