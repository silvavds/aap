#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "huffman.h"
#include "visuals.h"
	
#define PRINT_HUFFMAN 0
#define MAX_FILE_SIZE 50000000

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

typedef struct{
	char caractere;
	int numofbits;
	char * bincode;
} charFreq;

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
	printf("\n%d\n",numofencoding);
	sprintf(final_result,"%d\n",numofencoding);
	for(int i=0;i<MAX_CHARS;i++){
	 	if(caracteres[i].numofbits!=0){
	 		//printf("%d\n",caracteres[i].caractere);
			//printf("%c", caracteres[i].numofbits+32);
			printf("%c%c", caracteres[i].caractere,caracteres[i].numofbits+32);
			sprintf(final_result+strlen(final_result),"%c%c", caracteres[i].caractere,caracteres[i].numofbits+32);
	 	}
	}
	return caracteres;
}

void compress(char * str, FILE *fp){
	int i;
	int huffman [2 * MAX_CHARS -1] = {0}; // starts a huffman tree named huffman
	for(i = 0 ; i < (2 * MAX_CHARS -1) ; i++ ) huffman[i] = -256 ;
	t_ind_heap heap = {0};
	
	int total_normal = frequency_count(&heap, str);
	
	make_minimier(&heap);
		
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
	
	printf("total normal: %d \n", total_normal);	
	printf("total compressed: %d \n", total);
	printf("ratio: %5.2f %% \n", 100*(total/(double)total_normal));

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
	charFreq *newChar;
	char * final_result = (char*)calloc(MAX_FILE_SIZE,sizeof(char));
	newChar = print_table_from_num_of_bits(&caracteres[0], final_result);
	char currentC;
	int j;
	for(i=0;i<(int)(total_normal/8);i++){
		currentC = str[i];
		for(j=0;j<MAX_CHARS;j++){
			if(newChar[j].caractere==currentC){
				//printf("%s",newChar[j].bincode);
				sprintf(final_result+strlen(final_result),"%s",newChar[j].bincode);
			}
		}
	}
	printf("\n\n");
	print_huffman(heap, huffman, (heap.internal+127), heap.data);

	fputs(final_result,fp);

}

void decompress(char * str){
	char num_of_encoding[4];
	int i = 0;
	int str_cnt = 0;
	char ch = str[str_cnt];

	int stage = 0;

	charFreq * newChar;

	charFreq caracteres[MAX_CHARS];
	for(i = 0 ; i < MAX_CHARS ; i++){
		caracteres[i].caractere = 0;
		caracteres[i].numofbits=0;
		caracteres[i].bincode=NULL;
	}

	i=0;
	while(ch!=EOF){
		if(stage==0){ //Reading number of encoded caracters
			num_of_encoding[i]=ch;
			i++;
			str_cnt++;
			ch = str[str_cnt];
			if(ch=='\n'){
				stage=1;
				str_cnt++;
				ch = str[str_cnt];
			}
		}else if(stage==1){ //Creating characteres and frequencies
			int num_enc = atoi(num_of_encoding);
			char current_c;
			int current_count;
			for(i=0;i<(num_enc*2);i+=2){
				current_c = str[str_cnt+i];
				current_count = str[str_cnt+i+1]-32;
				caracteres[current_c].caractere = current_c;
				caracteres[current_c].numofbits = current_count;
			}
			newChar = table_from_num_of_bits(&caracteres[0],&num_enc);
			str_cnt += num_enc*2;
			ch = str[str_cnt];
			stage=2;
		}else if(stage==2){ //Decoding
			char * current_string = (char*)calloc(MAX_CODE_LEN,sizeof(char));
			while(ch!=EOF){
				sprintf(current_string+strlen(current_string),"%c",ch);
				str_cnt++;
				ch = str[str_cnt];
				for(i=0;i<MAX_CHARS;i++){
					if(newChar[i].bincode!=NULL){
						if(strcmp(newChar[i].bincode,current_string)==0){
							printf("%c",newChar[i].caractere);
							sprintf(current_string,"%c",'\0');
						}
						if(strlen(current_string)==(MAX_CODE_LEN-1)){
							i=MAX_CHARS;
							ch=EOF;
						}
					}
				}
			}
		}
	}
}

int main(int argc, char ** argv){
	if(argc==3){
		FILE *fp1 = fopen(argv[1], "r");
		char* input = (char*)calloc(MAX_FILE_SIZE,sizeof(char));
		char ch;
		do {
        	ch = fgetc(fp1);
        	sprintf(input+strlen(input),"%c", ch);
			// Checking if character is not EOF.
			// If it is EOF stop reading.
		} while (ch != EOF);
		input[strlen(input)-1]='\0';
		printf("String read: %s\n", input);
		fclose(fp1);


		FILE *fp2 = fopen(argv[2], "w");
		compress(input,fp2);
		fclose(fp2);
		//compress(argv[1]);
	}else if(argc==2){
		//printf("Decompress\n");
		FILE *fp = fopen(argv[1], "r");
		char* input = (char*)calloc(MAX_FILE_SIZE,sizeof(char));
		char ch;
		do {
        	ch = fgetc(fp);
        	sprintf(input+strlen(input),"%c", ch);
			// Checking if character is not EOF.
			// If it is EOF stop reading.
		} while (ch != EOF);
		input[strlen(input)-1]='\0';
		//printf("String read: %s\n", input);
		fclose(fp);
		decompress(input);
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







