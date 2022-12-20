#ifndef __HUFFMAN__

#define __HUFFMAN__

#define MAX_NUM 20		// ? 
#define MAX_CHARS 128		// max number of characters for encoding
#define MAX_CODE_LEN 50		// max len of a huffman code	
#define INIT_SIZE 100		

#define is_in_tree(i, n)	(i < n)		// computes if element makes part of tree
#define i_parent(i)		(i - 1)/2	// returns index of parent of element i
#define i_left_child(i)		(2 * i)+1	// returns index of the left child of element i
#define i_right_child(i)	(2 * i)+2  	// returns index of the right child of element i
#define i_last_internal(n)	n/2 -1		// computes the last internal node of a tree

// defines the data type for a heap
typedef struct {
	unsigned int nb_elt ;			// actual number of elements
	unsigned char tree [ MAX_CHARS ] ;	// array will describe the organization of the nodes
	int data [ 2 * MAX_CHARS -1 ] ;		// array will count the frequency of each char
	
	int internal ;				// stores the number of internal nodes
	// an internal node is considered to the made from grouping "pure" char nodes
	
} t_ind_heap ;	// change this name 

// defines the data type for "tracing" the way gone through of the heap
typedef struct {
	char str[MAX_CODE_LEN]; 	// maximun lenght a code can have
	int len;			// actual length of the code 
} t_trace ;

// important functions related to huffman codding

// simply inserts an element in the first available position in the heap
void naive_insert( t_ind_heap * heap , char value );

void print_heap_tree( t_ind_heap heap );

// 
void move_down ( t_ind_heap * tas, int index );

void move_up ( t_ind_heap * tas, int index );

int extract_root ( t_ind_heap * tas );

void make_minimier( t_ind_heap * heap );

void insert_internal( t_ind_heap * tas, int value);

int look_for ( t_ind_heap tas , int huffman[], int target, t_trace trace, int * encoding);

#endif
