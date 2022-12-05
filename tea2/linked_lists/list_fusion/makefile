all: output

main.o : main.c
	gcc -c main.c -o main.o
	
list.o : list.c
	gcc -c list.c -o list.o
	
stack_list.o : stack_list.c
	gcc -c stack_list.c -o stack_list.o
		
output : main.o list.o stack_list.o
	gcc main.o list.o stack_list.o -o output
	
clean :
	rm *.o
