
all: output
	#@echo "Le programme $(CIBLE) a été produit dans le répertoire $(REP)"

output : stack_cd.o elt.o main.o
	gcc -ggdb stack_cd.o elt.o main.o -o output -lm

main.o : main.c
	gcc -ggdb -c main.c -o main.o -lm
	
stack_cd.o : stack_cd.c
	gcc -ggdb -c stack_cd.c -o stack_cd.o
	
elt.o : elt.c
	gcc -ggdb -c elt.c -o elt.o	


