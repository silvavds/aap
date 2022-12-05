all: output

output : main.o list.o
	gcc main.o list.o -o output
	
main.o : main.c
	gcc -c main.c -o main.o
	
list.o : list.c
	gcc -c list.c -o list.o
	
clean :
	rm *.o
