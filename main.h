#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*#include <fcntl.h>
#include <glob.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>*/



#define MAX 1024 // utilisée pour les tailles de chaines
#define MAX_NB 16

//int compteLettre(char* tab, char lettre);
//void decompose(char* cmd, char** splited, int taille, char sep);
void separe(char* str, char** mots, int nbLettres, char caracSep);
int nbLettres(char* str);
int nbMots(char* str, char caracSep);
int recupCommande(char* str);
//void echo(char** str, int nbMots);
//void cat(char* nomFichier);
//void cd(char ** str);
//int export(char** str);
int commandePerso(char* str, char** mots, int taille);
//int wildcard(char* str, char** mots);
//int copier(char source[], char dest[]);
//int copie(int fs, int fd);
//void cp(char* source, char* destination);
//int type_fichier(char* source);
void retireCarac(char* str, char carac);
//void liberememoire(char** str1, int taille1, char** str2, int taille2);
void freeTab(char** str, int taille);
//void ls(char* str, int taille);*/

int helpTS(char* str, char** mots, int taille);
int helpMeta(char* str, char** mots, int taille);
int addTs(char* str, char** mots, int taille);
int addMeta(char* str, char** mots, int taille);
int showMeta(char* str, char** mots, int taille);
int showMetaI(char* str, char** mots, int taille);
int get(char* str, char** mots, int taille);
int stringToInt(char* str);
bool timeIsOk(int z, int date1, int date2, int timestamp);
bool valueIsOk(int y, int val1, int val2, int valeur);
bool idMetaIsOk(int x, int type, int idMeta);

// ****** STRUCTURES DE DONNEES ***** //

struct ts{
	int timestamp;
	int idMeta;
	int valeur;	
};
typedef struct ts TS;

struct metadata{
	int id;
	char* nom;
	char* typeCapteur;
	char* typeDonnees;
	char* unite;
	char* description
};
typedef struct metadata META;




/*
struct fichier
{
	char* nom;
	int fd;
	int perm;
	
};
typedef struct fichier FICHIER;
*/