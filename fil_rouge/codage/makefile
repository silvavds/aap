all : output

output : main.o huffman.o visuals.o
	gcc main.o huffman.o visuals.o -o codage
	
main.o : main.c
	gcc -c main.c -o main.o 
	
huffman.o : huffman.c
	gcc -c huffman.c -o huffman.o 	
	
visuals.o : visuals.c
	gcc -c visuals.c -o visuals.o	
	
clean: 
	rm *.o
	rm huffman/png/*.png
	rm huffman/dot/*.dot
	rm visuals/png/*.png
	rm visuals/dot/*.dot
