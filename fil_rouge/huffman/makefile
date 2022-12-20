all : output

output : main.o huffman.o
	gcc main.o huffman.o -o output 
	
main.o : main.c
	gcc -c main.c -o main.o 
	
huffman.o : huffman.c
	gcc -c huffman.c -o huffman.o 	
	
clean: 
	rm *.o
