//#include <stdio.h>
//#include <stdlib.h>
//#include "Types.h"
#include "main.h"
//#include "listeTs.h"

#define NB_BLOCK  10 /*16777215*/
#define NB_PAGES 63
#define NB_SEGMENT 3


int main(int argc, char **argv){
	
	int continuer = 1;
	while(continuer)
	{// boucle infinie dont on sort si l'utilisateur écrit "exit"
		char str[MAX]; // récupère ce qui est écrit par l'utilisateur
		fgets(str, MAX, stdin);
		if(feof(stdin)) // gère le CTRL+C
			exit(0);
		continuer = recupCommande(str);
	}
 
	return 0;
	
}


int recupCommande(char* str)
{//corps du programme
	retireCarac(str, '\n'); // enleve le \n laissé par fgets
	
	char** mots;	// remplis dans un tableau à 2 dimensions les différents mots de la commande
	char caracSep = ' ';
	char* exit1 = "exit";
	int tailleMotCommande = nbMots(str, caracSep); // compte le nombre de mots
	
	mots = calloc(MAX_NB, sizeof(char*)); // crée les sous tableaux
	separe(str, mots, strlen(str), caracSep); // remplis les mots dans les sous tableaux
	
	
	if(strcmp(exit1, mots[0]) == 0) //Si on a écrit exit => on quitte
		return 0;
	if(mots[0][0] == '\0')
		return 1;
		
	int cmdPerso = commandePerso(str, mots, tailleMotCommande);
		
}



int nbMots(char* str, char caracSep)
{// Compte le nombre de mots séparés par le caracSep
	int i = 0, cpt = 1;
	int taille = strlen(str);

	for(i = 0; i < taille; i++)
		if(str[i] == caracSep)
			cpt++;
	return cpt;
}

void separe(char* str, char** mots, int nbLettres, char caracSep)
{ // sépare la chaine de caractère en plusieurs mots
	char carac = caracSep;
	int taille = 0, nbMots = 0, cpt = 0;
	
	while( taille < nbLettres /*&& cpt < nbLettres*/)
	{//tant qu'on est pas à la fin du string
		if(str[taille] == carac)	
		{// Si on tombe sur un caractère séparateur
			mots[nbMots] = calloc(taille , sizeof(char)); // crée un nouveau mot dans le tableau
			strncpy(mots[nbMots], str, taille);			// on y copie le mot trouvé
			str = &str[taille + 1]; // reposition le début de la "tête" de lecture à la fin du mot ajouté
			taille = 0;
			nbMots++;
			cpt++;
		}
		else
		{
			cpt++;
			taille++;
		}
	} // Copie le dernier mot dans la liste des mots
	mots[nbMots] = calloc(taille, sizeof(char));
	strncpy(mots[nbMots], str, taille);
	
}

void retireCarac(char* str, char carac)
{//remplace la première occurence ce carac par un '\0'
	int i = 0; // enleve le \n de la commande
		for(i = 0; i < strlen(str); i++)
			if(str[i] == carac)
				str[i] = '\0';
}

int commandePerso(char* str, char** mots, int taille)
{// Verifie si la commande est handmade

	if(!strcmp("add", mots[0])){ // Commande d'ajout TS/meta
		if(!strcmp("-ts", mots[1])) // Commande d'ajout TS
			return addTs(str, mots, taille);
		else if(!strcmp("-meta", mots[1])) // Commande d'ajout meta
			return addMeta(str, mots, taille);
	}
	else if(!strcmp("help", mots[0])){
		/*if(!strcmp("-ts", mots[1])) // Commande d'aide TS
			return helpTS(str, mots, taille);
		else if(!strcmp("-meta", mots[1]))
			return helpMeta(str, mots, taille);*/
	}
	return 0;

}

int addTs(char* str, char** mots, int taille){
	if(taille < 5)
		printf("Nombre d'arguments insufisant pour ajouter une TS\n");
	else if(taille > 5)
		printf("Nombre d'arguements trop élevé pour ajouter une TS\n");
	else{
		printf("Ajout de la time series\n");
		FILE* fichierTs = NULL;
		fichierTs = fopen("TimeSeries.txt", "a+");
		if (fichierTs != NULL){
			fprintf(fichierTs, "%s %s %s\n", mots[2], mots[3], mots[4]);
			fclose(fichierTs);
			return 1;
		}
		else
			printf("Impossible d'ouvrir le fichier TimeSeries.txt\n");
	}
	return 0;
}

int addMeta(char* str, char** mots, int taille){
	if(taille < 8)
		printf("Nombre d'arguments insufisant pour ajouter une metadata\n");
	else if (taille > 8)
		printf("Nombre d'arguements trop élevé pour ajouter une metadata\n");
	else{
		printf("Ajout de la metadata\n");
		FILE* fichierMeta = NULL;
		fichierMeta = fopen("Metadata.txt", "a+");
		if (fichierMeta != NULL){
			fprintf(fichierMeta, "%s %s %s %s %s %s\n", mots[2], mots[3], mots[4], mots[5], mots[6], mots[7]);
			fclose(fichierMeta);
			return 1;
		}
		else
			printf("Impossible d'ouvrir le fichier Metadata.txt\n");
	}
	return 0;
}


/*
int main(int argc, char **argv)
{
	printf("hello world\n");
	NAND_FTL_free();
	return 0;
}

void NAND_FTL_free( void ){
	
	int i = 0, j =0;
	FILE* fichier = NULL;
	
	for(i = 0; i < NB_BLOCK; i++){
		char buf[64] = "";
		sprintf(buf, "%d", i);
		fichier = fopen(buf, "w+");
		
		for(j = 0; j < NB_PAGES; j++){
			fputs("0000\n0000\n0000\n0000\n", fichier);
		}
		fclose(fichier);
	}
}

*/
/*
 char str[10] = "";
    int nombre = 12345;
    sprintf(str, "%d", nombre);
    printf("%d", nombre);*/