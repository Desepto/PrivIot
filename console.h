#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <glob.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>



#define MAX 1024
#define MAX_NB 50

int compteLettre(char* tab, char lettre);
void decompose(char* cmd, char** splited, int taille, char sep);
void separe(char* str, char** mots, int nbLettres, char caracSep);
int nbLettres(char* str);
int nbMots(char* str, char caracSep);
int recupCommande(char* str);
void echo(char** str, int nbMots);
void cat(char* nomFichier);
void cd(char ** str);
int export(char** str);
int commandePerso(char* str, char** mots, int taille);
int wildcard(char* str, char** mots);
int copier(char source[], char dest[]);
int copie(int fs, int fd);
void cp(char* source, char* destination);
int type_fichier(char* source);
void retireCarac(char* str, char carac);
void liberememoire(char** str1, int taille1, char** str2, int taille2, char* str3);
void freeTab(char** str, int taille);
void ls(char* str, int taille);

struct fichier
{
	char* nom;
	int fd;
	int perm;
	
};
typedef struct fichier FICHIER;
