#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <sys/stat.h>
#include <math.h> 
#include "visuals.h"

// ceil, floor : #include <math.h>

#define isINTREE(i,n)			(i<n)
#define iPARENT(i) 			(i-1)/2
#define iLCHILD(i) 			(2*i)+1
#define iRCHILD(i) 			(2*i)+2

char * outputPath = "./ex1";

int main(void) {


	int ex1[] = { 18, 15, 11, 10, 15, 6, 1, 7, 4, 9};   	// 10
	int ex2[] = { 18, 16, 11, 10, 15, 6, 1, 7, 4, 9, 3}; 	// 11
	int ex3[] = { 3, 1, 8, 5, 9, 6, 11, 7, 4, 12, 0 }; 	// 10
	int ex4[] = { 7, 15, 1, 9, 15, 10, 11, 4, 18, 6 }; 	// 10 
	
	// affichage pseudo graphique 
	showPOT(ex4, 10); 
	
	// affichage graphique 
	// NB: penser à changer la valeur de la variable globale outputPath pour spécifier le chemin de création des sous-répertoires
	createDotPOT(ex1, 10,"tas"); 
	
}

void showPOT(int t[], int n) {

	printf("show POT (partilly ordered three) (nb_elt : %d)\n",n);
	showPOT_rec(t, n, 0, 0); 
}

void showPOT_rec(int t[], int n, int root, int indent) {
	// affiche récursivement en mode pseudo graphique 
	// ordre de récurrence  : taille du sous-arbre 
	int i; 
	
	if (! isINTREE(root,n)) return;  
	
	showPOT_rec(t, n, iRCHILD(root), indent+1);
	for(i=0;i<indent;i++) {
		printf("\t"); 
	}
	printf("%d[%d]\n",t[root], root);
	showPOT_rec(t, n, iLCHILD(root), indent+1);
}


static void genDotPOT_rec(int t[], int n, int root, FILE *fp){
	// Attention : les fonction toString utilisent un buffer alloué comme une variable statique 
	// => elles renvoient toujours la même adresse 
	// => on ne peut pas faire deux appels à toString dans le même printf()

	if (! isINTREE(root,n)) return; // cas de base 
	
	// cas général 
	fprintf(fp, "\t%d",root); 
	fprintf(fp, " [label = \"%d\"];\n",t[root]);

	if (isINTREE(iLCHILD(root),n)) {
		fprintf(fp, "\t%d:sw",root);
		fprintf(fp, " -> %d;\n", iLCHILD(root));
		genDotPOT_rec(t,n,iLCHILD(root), fp);
	}

	if (isINTREE(iRCHILD(root),n)) {
		fprintf(fp, "\t%d:se",root);
		fprintf(fp," -> %d;\n", iRCHILD(root));
		genDotPOT_rec(t,n,iRCHILD(root), fp);
	} 

}


void createDotPOT(int t [], int n,const char *basename) {
	static char oldBasename[FILENAME_MAX + 1] = "";
	static unsigned int noVersion = 0;

	char DOSSIER_DOT[FILENAME_MAX + 1]; 
	char DOSSIER_PNG[FILENAME_MAX + 1]; 

	char fnameDot [FILENAME_MAX + 1];
	char fnamePng [FILENAME_MAX + 1];
	char	cmdLine [2 * FILENAME_MAX + 20];
	FILE *fp;
	struct stat sb;
	

	// Au premier appel, création (si nécessaire) des répertoires
	// où seront rangés les fichiers .dot et .png générés par cette fonction	

	// il faut créer le répertoire outputPath s'il n'existe pas 
	if (stat(outputPath, &sb) == 0 && S_ISDIR(sb.st_mode)) {
    } else {
        printf("Création du répertoire %s\n", outputPath);
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

	if (strcmp(oldBasename, basename) != 0) {
		noVersion = 0;
		strcpy(oldBasename, basename); 
	}

	sprintf(fnameDot, "%s%s_v%02u.dot", DOSSIER_DOT, basename, noVersion);
	sprintf(fnamePng, "%s%s_v%02u.png", DOSSIER_PNG, basename, noVersion);

	CHECK_IF(fp = fopen(fnameDot, "w"), NULL, "erreur fopen dans saveDotBST"); 
	
	noVersion ++;
	fprintf(fp, "digraph %s {\n", basename);
	fprintf(fp, 
	"\tnode [\n"
		"\t\tfontname  = \"Arial bold\" \n"
		"\t\tfontsize  = \"14\"\n"
		"\t\tfontcolor = \"red\"\n"
		"\t\tstyle     = \"rounded, filled\"\n"
		"\t\tshape     = \"circle\"\n"
		"\t\tfillcolor = \"grey90\"\n"
		"\t\tcolor     = \"blue\"\n"
		"\t\twidth     = \"0.5\"\n"
		"\t]\n"
	"\n"
	"\tedge [\n"
		"\t\tcolor     = \"blue\"\n"
	"\t]\n\n"
	);


	genDotPOT_rec(t,n,0,fp);

	fprintf(fp, "}\n");	
	fclose(fp);

	sprintf(cmdLine, "dot -Tpng  %s -o %s", fnameDot, fnamePng);
	system(cmdLine);

	printf("Creation de '%s' et '%s' ... effectuee\n", fnameDot, fnamePng);
}















