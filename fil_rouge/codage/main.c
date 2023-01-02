#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "huffman.h"
#include "visuals.h"

// important discussion on how different hufmann codes can be equally efficient
// https://stackoverflow.com/questions/16873886/variations-in-huffman-encoding-codewords
	
#define PRINT_HUFFMAN 0

typedef struct{
	char caractere;
	int numofbits;
	char * bincode;
} charFreq;

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


int cfcmp(const void *p1, const void *p2) {
    if(((charFreq*)p1)->numofbits<((charFreq*)p2)->numofbits){
		return -1;
	}else if(((charFreq*)p1)->numofbits==((charFreq*)p2)->numofbits){
		if(((charFreq*)p1)->caractere<((charFreq*)p2)->caractere){
			return -1;
		}
	}else{
		return 1;
	}
}

char* stradd(const char* a, const char* b){
    size_t len = strlen(a) + strlen(b);
    char *ret = (char*)malloc(len * sizeof(char) + 1);
    *ret = '\0';
    return strcat(strcat(ret, a) ,b);
}

char * bin(unsigned n,unsigned max) {
    unsigned i;
	char * result = (char*)calloc(max,sizeof(char));
	int counter=0;
    for (i = 1 << max; i > 0; i = i / 2){
        if(n & i){
			result[counter]='1';
		}else{
			result[counter]='0';
		}
		counter++;
	}
	return &result[1];
}

charFreq * table_from_num_of_bits(charFreq * caracteres, int* num_of_encoding){
	qsort(&caracteres[0],MAX_CHARS,sizeof(charFreq),cfcmp);
	int last=0;
	*num_of_encoding=0;
	for(int i = 0 ; i < MAX_CHARS ; i++){
		if(caracteres[i].numofbits!=0){
			(*num_of_encoding)++;
			caracteres[i].bincode = bin(last,caracteres[i].numofbits);
			//printf("%s %c%d\t",caracteres[i].bincode, caracteres[i].caractere,caracteres[i].numofbits);
			//printf("(%d,%d) %c%d\t",last, caracteres[i].numofbits,caracteres[i].caractere,caracteres[i].numofbits);
			last++;
			last = last<<(caracteres[i+1].numofbits-caracteres[i].numofbits);
		}
	}
	return caracteres;
}

charFreq * print_table_from_num_of_bits(charFreq * caracteres, char* final_result){
	int * numenc;	
	table_from_num_of_bits(caracteres,numenc);
	int numofencoding = *numenc;
	if(VERBOSE){
		printf("\n%d\n",numofencoding);
	}
	sprintf(final_result,"%d\n",numofencoding);
	for(int i=0;i<MAX_CHARS;i++){
	 	if(caracteres[i].numofbits!=0){
	 		//printf("%d\n",caracteres[i].caractere);
			//printf("%c", caracteres[i].numofbits+32);
			if(VERBOSE){
				printf("%c%c", caracteres[i].caractere,caracteres[i].numofbits+32);
			}
			sprintf(final_result+strlen(final_result),"%c%c", caracteres[i].caractere,caracteres[i].numofbits+32);
	 	}
	}
	return caracteres;
}


int main(int argc, char ** argv){
	int i,j;
	
	int huffman [2 * MAX_CHARS -1] = {0}; // starts a huffman tree named huffman
	
	for(i = 0 ; i < (2 * MAX_CHARS -1) ; i++ ) huffman[i] = -256 ;
	
	t_ind_heap heap = {0};
	
	// sample text for testing
	//char * str = "algorithme de huffman pour la compression de chaines";
	//char str[] = "ABBACADABRA";
	//char str[] = "this is an example of a huffman tree";
	//char str[] = "streets are stone stars are not";
	
	/* read from input */
	//printf("argc: [%d] \n", argc);
	
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
	//createDotPOT(heap.tree, heap.nb_elt, "heap_vis"); 
	
	make_minimier(&heap);
	//print_heap_tree(heap);
	
	//createDotPOT(heap.tree, heap.nb_elt, "heap_vis", heap.data); 
		
	while ( heap.nb_elt > 1 ){
		// extract the root
		int x = extract_root( &heap );
		int y = extract_root( &heap );
		insert_internal( &heap, heap.data[x]+heap.data[y] );
		
		huffman[x] = -1*(heap.internal+127);	
		huffman[y] = +1*(heap.internal+127);	
		#if(PRINT_HUFFMAN == 1)		
		print_huffman(heap, huffman, (heap.internal+127), heap.data);
		#endif
	}
	
	// make table encoding
	t_trace trace = {0} ; 	
	
	// will store the number of bits that each chars (the index) uses
	int encoding [MAX_CHARS] = {0} ;
	int * p_encoding = &encoding[0] ;
	
	int total = look_for( heap, huffman, heap.tree[0], trace, p_encoding);
	
		
	charFreq caracteres[MAX_CHARS];
	
	for(i = 0 ; i < MAX_CHARS ; i++){
		if(encoding[i] != 0){
			caracteres[i].caractere = i;
			caracteres[i].numofbits = encoding[i];
			caracteres[i].bincode=NULL;
		}else{
			caracteres[i].caractere = 0;
			caracteres[i].numofbits=0;
			caracteres[i].bincode=NULL;
		}
	}
		
	int num_of_chars = 0;	
	charFreq *newChar;
	newChar = table_from_num_of_bits(&caracteres[0], &num_of_chars);
	
	printf("\ncar : occ | long | bits\n");
	printf("----+-----+------+--------\n");
	
	for(i = 0 ; i < MAX_CHARS ; i++){
		if(encoding[i] != 0){
			
			for(j = MAX_CHARS - num_of_chars; j < MAX_CHARS ; j++){
				if( caracteres[j].caractere == i)break;
				//printf("[%c] [%s] \n", caracteres[i].caractere, caracteres[i].bincode, valid2);
			}
	
			printf("\'%c\' :%4d |%5d | %s \n", i, encoding[i], heap.data[i], caracteres[j].bincode);
		}
	}
	printf("\n");
	
	
	char currentC;
	for(i=0;i<(int)(total_normal/8);i++){
		currentC = str[i];
		for(j = 0 ; j<MAX_CHARS ; j++){
			if(newChar[j].caractere == currentC){
				printf("%s",newChar[j].bincode);
				//sprintf(final_result+strlen(final_result),"%s",newChar[j].bincode);
			}
		}
	}
	printf("\n\n");
	
	printf("total normal: %d \n", total_normal);	
	printf("total compressed: %d \n", total);
	printf("ratio: %5.2f %% \n", 100*(total/(double)total_normal));


	print_huffman(heap, huffman, (heap.internal+127), heap.data);
		
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







