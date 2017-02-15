//#include <stdio.h>
//#include <stdlib.h>
//#include "Types.h"
#include "main.h"
//#include "listeTs.h"

#define NB_BLOCK  10 /*16777215*/
#define NB_PAGES 63
#define NB_SEGMENT 3


int main(int argc, char **argv){
	//contient la boucle du programme
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
{//transforme ce qu'on reçoit en un tableau à 2 dim de mots
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
{// Redigire vers bonnes fonctions
	if(!strcmp("add", mots[0])){ // Commande d'ajout TS/meta
		if(!strcmp("-ts", mots[1])) // Commande d'ajout TS
			return addTs(str, mots, taille);
		else if(!strcmp("-meta", mots[1])) // Commande d'ajout meta
			return addMeta(str, mots, taille);
	}
	else if(!strcmp("help", mots[0])){
		if(!strcmp("-ts", mots[1])) // Commande d'aide TS
			return helpTS(str, mots, taille);
		else if(!strcmp("-meta", mots[1])) // Commande d'aide Meta
			return helpMeta(str, mots, taille);
	}
	else if(!strcmp("show", mots[0])){
		if(taille > 1 && !strcmp("-i", mots[1])) // Commande d'aide affichage d'un capteur particulier
			return showMetaI(str, mots, taille);
		else // Commande d'affichage de tous les capteurs
			return showMeta(str, mots, taille);
	}
	return 0;

}

int helpTS(char* str, char** mots, int taille){
	//Fonction d'affichage de l'aide des TS
	if(taille == 2){
		printf("Une TimeSeries est constituee de 3 attributs :\n *Son timestamp \n *L'id correspondant à son capteur (il doit faire partie de la liste des metadata) \n * Sa valeur (int) ");
		printf("Il faut indiquer les differents elements dans l'ordre indique lors de l'ajout d'une timeseries.\n");
		return 1;
	}
	return 0;
}

int helpMeta(char* str, char** mots, int taille){
	// Fonctions de l'affichage de l'aide des metadatas
	if(taille == 2 ){
		printf("Une Metada est constituee de 6 attributs :\n *Son id (normalement defini par l'application) \n *Son nom (32 char max) \n *Son type de capteur (32 char max)\n"); 
		printf(" *Le type des donnees mesurees (32 char max)\n *L'unite de mesure (32 char max)\n *La description du capteur (128 char max)\n ");
		printf("Il faut indiquer les differents elements dans l'ordre indique lors de l'ajout d'une metadata.\n");
		return 1;
	}
	return 0;
}

int addTs(char* str, char** mots, int taille){
	//Fonciton d'ajout d'une TS
	if(taille < 5)
		printf("Nombre d'arguments insufisant pour ajouter une TS\n");
	else if(taille > 5)
		printf("Nombre d'arguements trop eleve pour ajouter une TS\n");
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

// Il faudrait faire en sorte que l'id soit donné automatiquement et non pas choisi (fichier avec un lastID)
int addMeta(char* str, char** mots, int taille){
	//Fonction d'ajout d'une metadata
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

int showMeta(char* str, char** mots, int taille){
	char* text;
	text = calloc(MAX, sizeof(char));
	
	FILE* fMeta = NULL;
	fMeta = fopen("Metadata.txt", "r");
	
	if(fMeta != NULL){
		while(fgets(text, MAX, fMeta) != NULL)
			printf(text);
		fclose(fMeta);
		free(text);
		return 1;
	}
	else
		printf("Aucune metada enregistrée");
	return 0;
}

int showMetaI(char* str, char** mots, int taille, int indice){
	return 0;
}