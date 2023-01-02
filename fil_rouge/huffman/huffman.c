#include "huffman.h"
#include "visuals.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <sys/stat.h>
#include <math.h> 

#define PRINT_TREE 0

// simply inserts an element in the first available position in the heap
void naive_insert( t_ind_heap * heap , char value ){
	int i = ( heap->nb_elt += 1 ); 
	heap->tree[ i - 1 ] = value ;
}

void print_heap_tree( t_ind_heap heap ){
	int i;
	
	for( i = 0 ; i < heap.nb_elt ; i++){ 
		printf("[%d(%c)(%d)] ", heap.tree[i], heap.tree[i], heap.data[heap.tree[i]] ); 
	}
	printf(" nb_elt: %d", heap.nb_elt);
	printf("\n");	
}

void make_minimier( t_ind_heap * heap ){
	int i;
	//printf("minimizing \n");
	for( i = i_last_internal( heap->nb_elt ) ; i >= 0 ; i-- ){
		move_down ( heap , i );
		
		#if(PRINT_TREE == 1)
		createDotPOT(heap->tree, heap->nb_elt, "minimier", heap->data); 
		#endif
		//print_heap_tree( *heap );
	}
}

int extract_root ( t_ind_heap * tas ){
	int index = tas->nb_elt - 1 ;
	
	int last = tas->tree[ index ] ;
	int first = tas->tree[ 0 ] ;
	tas->nb_elt--;
	
	tas->tree[ 0 ] = last;
	tas->tree[ index ] = first;
		
	//printf("removing \n");
	//show_pot(tas->tree , tas->nb_elt);  	
	move_down ( tas , 0 );	// make the root go down
	//show_pot(tas->tree , tas->nb_elt);  	
	
	//return tas->tree[ index ] ;
	return first ;
}	

//uses minimier
void move_up ( t_ind_heap * tas, int index ){
	
	// to access the 10th element index must be 9
	
	// *(removes this "debbug" code)*
	//printf("[%d] [%d] [%d] [%d] \n", index, i_parent(index), tas->tree[ index ], tas->tree[ i_parent(index) ] );
	
	// while node is not the root 
	// and its value is larger than its father
	#if(PRINT_TREE == 1)
	createDotPOT(tas->tree, tas->nb_elt, "move_up", tas->data); 
	#endif
	
	while( index > 0 && tas->data[ tas->tree[ index ] ] < tas->data [ tas->tree[ i_parent(index) ] ] ){
	//while( index > 0 && tas->data[ tas->tree[ index ] ] < tas->data [ tas->tree[ i_parent(index) ] ] || 
 	//	(  tas->data[ tas->tree[ index ] ] == tas->data [ tas->tree[ i_parent(index) ] ] && tas->tree[ index ] < tas->tree[ i_parent(index) ] ) ){
			
		int aux = tas->tree[ i_parent( index ) ];
		tas->tree[ i_parent( index ) ] = tas->tree[ index ];
		tas->tree[ index ] = aux;
		
		index = i_parent( index );
		
		// *(removes this "debbug" code)*
		//printf("[%d] [%d] [%d] [%d] \n", index, i_parent(index), tas->tree[ index ], tas->tree[ i_parent(index) ] );
		#if(PRINT_TREE == 1)
		createDotPOT(tas->tree, tas->nb_elt, "move_up", tas->data); 
		#endif
	}
	
}

void insert_internal( t_ind_heap * tas, int value){

	//inserts in the first available position
	int position = tas->internal + 128;
	tas->internal += 1;
	tas->data[position] = value;
	
	//printf("internal: %d [%d] \n", tas->data[position], tas->internal);
		
	naive_insert(tas, position );
	move_up( tas , tas->nb_elt - 1 );
	
	
}

int look_for ( t_ind_heap tas , int huffman[], int target, t_trace trace, int * encoding){
	
	int i,j;
	
	int total = 0;
	//printf("need to look for [%d] and [%d] \n", target, -target);
	
	for( i = 0 ; i < MAX_CHARS * 2 - 1 ; i++ ){
		
		if( huffman[ i ] == target || huffman[ i ] == target*-1 ){
			trace.len++;
			
			//printf("found %d! ", target);
			
			if( huffman[i] > 0 ){ 		// right child			
				trace.str[trace.len - 1] = '1';
				//printf(" NEXT! %d", trace_n );
			}
				
			else {
				trace.str[trace.len - 1] = '0';				
			}
						
			if( i < 128){
				//printf("-> this is a number: [%c/%4d] - [%2d] ", i, i, tas.data[i]);
				
				encoding[i] = trace.len;
				total += tas.data[i] * trace.len;				
								
				//for(j = 0 ; j < trace.len ; j++ )printf("%c ", trace.str[j]); printf("\n");
				trace.len -= 1;
								
			}
			else{
				//printf("now gonna look for %d! ", i); for(j = 0 ; j < trace.len ; j++ )printf("%c ", trace.str[j]); printf("\n");
				total += look_for( tas, huffman, i, trace, encoding);
				trace.len -= 1;
				
			}
					
		}
	
	}
	
	return total;	
}

void swap( t_ind_heap * tas , int index_parent, int index_child ){
	int aux = tas->tree[ index_child ];
	tas->tree[ index_child ] = tas->tree[ index_parent ];
	tas->tree[ index_parent ] = aux;		
}

void move_down ( t_ind_heap * tas, int index ){
	#if(PRINT_TREE == 1)
	createDotPOT(tas->tree, tas->nb_elt, "move_down", tas->data); 	
	#endif
	// while it is smaller than any of its children
	while( is_in_tree(i_left_child(index), tas->nb_elt) || is_in_tree(i_right_child(index), tas->nb_elt) ){
		
		//show_pot(tas->tree , tas->nb_elt);  
		int aux = 0; 
		
		if( is_in_tree(i_left_child(index), tas->nb_elt) && is_in_tree(i_right_child(index), tas->nb_elt) ){ 	// if it has both child

			// if an exchange has to be made
			if( tas->data[ tas->tree[ index ] ] > tas->data [ tas->tree[ i_left_child(index) ] ] || tas->data[ tas->tree[ index ] ] > tas->data[ tas->tree[ i_right_child(index) ] ] ){
				
				// exchange with the left
				if( tas->data [ tas->tree[ i_left_child(index) ] ] < tas->data [ tas->tree[ i_right_child(index) ] ] ){
					swap( tas , index, i_left_child( index ) );			
					index = i_left_child( index );
				}
				// exchange with the one with lower value
				else if( tas->data [ tas->tree[ i_left_child(index) ] ] == tas->data [ tas->tree[ i_right_child(index) ] ]  ){
					
					// if left is smaller
					//if( tas->tree[ i_left_child(index) ] < tas->tree[ i_right_child(index) ] ){
					
					if(1){	// exchance always with left
						//exchange with left
						swap( tas , index, i_left_child( index ) );		
						index = i_left_child( index );
					}
					else{
						//exchange with right
						swap( tas , index, i_right_child( index ) );		
						index = i_right_child( index );
					}					
				}
				// exchange with the right
				else{
					swap( tas , index, i_right_child( index ) );		
					index = i_right_child( index );
				}
			}
			else{
				break;
			}		
				
		}
		else if ( is_in_tree(i_left_child(index), tas->nb_elt) ){	// it has only left child
							
			// if an exchange has to be made
			if( tas->data[ tas->tree[ index ] ] > tas->data [ tas->tree[ i_left_child(index) ] ] ){
				swap( tas , index, i_left_child( index ) );		
				index = i_left_child( index );
			}
			else{	
				//printf("nothing has to be made! \n");
				break;
			}
			
		}
		
	#if(PRINT_TREE == 1)
	createDotPOT(tas->tree, tas->nb_elt, "move_down", tas->data); 	
	#endif
	}
}

void print_huffman ( t_ind_heap tas , int huffman[], int target, int data[]){
	
	char * basename = "tree";
	char * outputPath = "./huffman";
	//printf("FILENAME_MAX: %d \n", FILENAME_MAX);
	
	static char oldBasename[FILENAME_MAX + 1] = "";
	
	static unsigned int noVersion = 0;
	
	//int nb_files = system("ls visuals/png/* | wc -l");
	//printf("nb_files: %d   \n", noVersion);
		
	char DOSSIER_DOT[FILENAME_MAX/2 + 1]; 
	char DOSSIER_PNG[FILENAME_MAX/2 + 1]; 
	
	char fnameDot [FILENAME_MAX + 1];
	char fnamePng [FILENAME_MAX + 1];
	char cmdLine [2 * FILENAME_MAX + 20];
	FILE *fp;
	struct stat sb;
	
	// Au premier appel, création (si nécessaire) des répertoires
	// où seront rangés les fichiers .dot et .png générés par cette fonction	

	// il faut créer le répertoire outputPath s'il n'existe pas 
	if (stat(outputPath, &sb) == 0 && S_ISDIR(sb.st_mode)) {
   	}
   	else {
        	//printf("Création du répertoire %s\n", outputPath);
		mkdir(outputPath, 0777);
    	}

	// il faut créer les répertoires outputPath/png et /dot 
	sprintf(DOSSIER_DOT, "%s/dot/",outputPath);
	sprintf(DOSSIER_PNG, "%s/png/",outputPath);

	if (oldBasename[0] == '\0') {
		mkdir(DOSSIER_DOT,	S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);
		mkdir(DOSSIER_PNG,	S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);
	}

	 // S'il y a changement de nom de base alors recommencer à zéro
	 // la numérotation des fichiers 

	/*
	if (strcmp(oldBasename, basename) != 0) {
		noVersion = 0;
		strcpy(oldBasename, basename); 
	}
	*/

	sprintf(fnameDot, "%sv_%05u_%s.dot", DOSSIER_DOT, noVersion, basename);
	sprintf(fnamePng, "%sv_%05u_%s.png", DOSSIER_PNG, noVersion, basename);
	
	CHECK_IF(fp = fopen(fnameDot, "w"), NULL, "erreur fopen dans saveDotBST"); 
	
	noVersion ++;
	
	fprintf(fp, "digraph %s {\n", basename);
		
	fprintf(fp, 
	"\tnode [fontname=\"Arial\", shape=\"circle\", width=0.5]; \n\n"
	);

	print_huffman_rec( tas, huffman, target, fp, data);

	fprintf(fp, "}\n");	
	fclose(fp);

	sprintf(cmdLine, "dot -Tpng  %s -o %s", fnameDot, fnamePng);
	system(cmdLine);

	//printf("Creation de '%s' et '%s' ... effectuee\n", fnameDot, fnamePng);	

}

void print_huffman_rec ( t_ind_heap tas , int huffman[], int target, FILE * fp, int data[]){
	
	int i,j;
	
	int total = 0;
	static unsigned int flag = 0;
	
	if(flag == 0){
		
		flag++;
	}
	
	//printf("need to look for [%d] and [%d] \n", target, -target);
	
	for( i = 0 ; i < MAX_CHARS * 2 - 1 ; i++ ){
		
		if( huffman[ i ] == target || huffman[ i ] == target*-1 ){
			//trace.len++;
			
			//printf("found %d! ", target);
			
			if( huffman[i] > 0 ){ 		// right child			
				//   printf("%d:se -> %d [label = \" 1\"]; \n", abs( huffman[i] ), i);				
				fprintf(fp, "%d:se -> %d [label = \" 1\"]; \n", abs( huffman[i] ), i);
				//trace.str[trace.len - 1] = '1';
				//printf(" NEXT! %d", trace_n );
			}
				
			else {
				//   printf("%d:sw -> %d [label = \" 0\"]; \n", abs( huffman[i] ), i);				
				fprintf(fp, "%d:sw -> %d [label = \" 0\"]; \n", abs( huffman[i] ), i);
				//trace.str[trace.len - 1] = '0';				
			}
			
			if( i < 128 && i != '"'){
				//printf("-> this is a number: [%c/%4d] - [%2d] ", i, i, tas.data[i]);
				
				//encoding[i] = trace.len;
				//total += tas.data[i] * trace.len;				
								
				//for(j = 0 ; j < trace.len ; j++ )printf("%c ", trace.str[j]); printf("\n");
				//trace.len -= 1;
				//   printf("%d [label = \"%d\"]; \n", abs( i ), abs( i ) );
				fprintf(fp, "%d [label = \"[%c] (%d) \"]; \n", abs( i ), abs( i ), data[abs( i ) ] );

			}
			else{
				//printf("now gonna look for %d! ", i); for(j = 0 ; j < trace.len ; j++ )printf("%c ", trace.str[j]); printf("\n");
				//   printf("%d [label = \"%d\"]; \n", abs( i ), abs( i ) );
				fprintf(fp, "%d [label = \"%d\"]; \n", abs( i ), abs( i ) );
				//fprintf(fp, "digraph %s {\n", basename);
				
				print_huffman_rec(tas, huffman, i, fp, data);
				
				//trace.len -= 1;
				
				
			}
			
		
		}
	
	}
	
}
