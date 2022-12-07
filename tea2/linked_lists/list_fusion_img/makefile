all: output

visuals.o : visuals.c
	gcc -c visuals.c -o visuals.o

main.o : main.c
	gcc -c main.c -o main.o
	
list.o : list.c
	gcc -c list.c -o list.o
	
stack_list.o : stack_list.c
	gcc -c stack_list.c -o stack_list.o
			
output : list.o stack_list.o visuals.o main.o 
	gcc main.o list.o stack_list.o visuals.o -o output
	
clean :
	rm *.o
