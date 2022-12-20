#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "huffman.h"

// important discussion on how different hufmann codes can be equally efficient
// https://stackoverflow.com/questions/16873886/variations-in-huffman-encoding-codewords
	


// counts the frequency of each char
int frequency_count( t_ind_heap * heap, char * str){
	long i;
	long length = strlen(str) ;
	// adds up any char in the string
	for( i = 0 ; i < length ; i++){
		heap->data[ str[i] ] += 1;
	}
	
	// inserts in the tree chars that have at least 1 occurance in alphabetic order
	for( i = 0 ; i < MAX_CHARS ; i++){
		if( heap->data[ i ] != 0 )
			naive_insert( heap , i );		
	}
	
	return strlen(str)*8;
}

char * read_from_file();
char * read_from_stdin();

int main(int argc, char ** argv){
	int i;
	
	int huffman [2 * MAX_CHARS -1] = {0}; // starts a huffman tree named huffman
	
	for(i = 0 ; i < (2 * MAX_CHARS -1) ; i++ ) huffman[i] = -256 ;
	
	t_ind_heap heap = {0};
	
	// sample text for testing
	//char * str = "algorithme de huffman pour la compression de chaines";
	//char str[] = "ABBACADABRA";
	//char str[] = "this is an example of a huffman tree";
	//char str[] = "streets are stone stars are not";
	
	printf("argc: [%d] \n", argc);
	
	char * str = NULL;
	
	if(argc == 1){
		str = read_from_stdin();	
	}
	else{
		str = argv[1];
	}
	
	//char * str = read_from_file();
	
	int total_normal = frequency_count(&heap, str);

	//print_heap_tree(heap);
	make_minimier(&heap);
	//print_heap_tree(heap);
	
	while ( heap.nb_elt > 1 ){
		// extract the root
		int x = extract_root( &heap );
		int y = extract_root( &heap );
		insert_internal( &heap, heap.data[x]+heap.data[y] );
		
		huffman[x] = -1*(heap.internal+127);	
		huffman[y] = +1*(heap.internal+127);			
	}
	
	// make table encoding
	t_trace trace = {0} ; 	
	
	// will store the number of bits that each chars (the index) uses
	int encoding [MAX_CHARS] = {0} ;
	int * p_encoding = &encoding[0] ;
	
	int total = look_for( heap, huffman, heap.tree[0], trace, p_encoding);
	
	printf("total normal: %d \n", total_normal);	
	printf("total compressed: %d \n", total);
	printf("ratio: %5.2f %% \n", 100*(total/(double)total_normal));
	
	for(i = 0 ; i < MAX_CHARS ; i++){
		if(encoding[i] != 0){
			printf("--> [%c/%4d] - [%2d] - [%8d] \n", i, i, encoding[i], heap.data[i]);
		}
	}
	
}

char * read_from_file(){
	FILE * fp = fopen("hurricane.txt", "r");
	
	fseek(fp, 0, SEEK_END);
	long file_size = ftell(fp);
	fseek(fp, 0, SEEK_SET);  
	
	char * str = (char *)malloc(sizeof(char) * file_size);
	fread(str, file_size, sizeof(char), fp);
	
	fclose(fp);
	
	return str;
}

char * read_from_stdin(){
	// read one char at a time until EOF
	// if it gets to the size of INIT_SIZE 
	// 	then doubles is an reallocs more memory
	
	long file_size = INIT_SIZE;
	
	char * str = (char *)malloc(sizeof(char) * file_size);
	
	//fread(str, file_size, sizeof(char), stdin);

	int index = 0;
	str[index] = fgetc(stdin);
		
	while(str[index] != EOF){
		index++;
		
		if( index > file_size -1 ){
			file_size *= 2;
			str = (char *)realloc(str, sizeof(char) * file_size );
		}
		
		str[index] = fgetc(stdin);
	}
		
	return str;
}







