PWD=$(shell pwd)
REP=$(shell basename $(PWD))
SOURCES=$(shell cat makefile_sources)
CIBLE=$(REP).exe
CFLAGS=-Wall

# makefile générique pour produire un code source 
# dont le nom correspond au nom du répertoire qui le contient

all: output
	@echo "Le programme $(CIBLE) a été produit dans le répertoire $(REP)"

output : $(SOURCES)
	@echo -n "Production de $(CIBLE)"
	@echo " à partir des fichiers : $(SOURCES)"
	gcc -ggdb $(CFLAGS) $(SOURCES) -o output

clean: 
	@echo "Nettoyage de $(CIBLE)"
	@rm -rf $(CIBLE)
