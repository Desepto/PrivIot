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

	
	//Morceau de code qui permet de lire à partir d'une certaine ligne !
	char text[MAX];
	FILE* f = NULL;
	f = fopen("TimeSeries.txt", "r");
	int tailleLigne = ((sizeof(int) * 3) + (sizeof(char)));
	
	if (f != NULL){
		fseek(f, tailleLigne, SEEK_SET);
		while(fgets(text, MAX, f) != NULL){
			
			printf("%s", text);
		}
		fclose(f);
		
	}
	
	/*
	int continuer = 1;
	while(continuer)
	{// boucle infinie dont on sort si l'utilisateur écrit "exit"
		char str[MAX]; // récupère ce qui est écrit par l'utilisateur
		fgets(str, MAX, stdin);
		if(feof(stdin)) // gère le CTRL+C
			exit(0);
		continuer = recupCommande(str);
	}
 */
	return 0;
	
}


int recupCommande(char* str)
{//Génère le tableau de mots
	retireCarac(str, '\n'); // enleve le \n laissé par fgets
	
	char** mots;	// remplis dans un tableau à 2 dimensions les différents mots de la commande
	char caracSep = ' ';
	char* exit1 = "exit";
	int tailleMotCommande = nbMots(str, caracSep); // compte le nombre de mots
	
	mots = calloc(MAX_NB, sizeof(char*)); // crée les sous tableaux
	separe(str, mots, strlen(str), caracSep); // remplis les mots dans les sous tableaux
	
	
	if(strcmp(exit1, mots[0]) == 0){ //Si on a écrit exit => on quitte
		freeTab(mots, MAX_NB);
		return 0;
	}
	
	if(mots[0][0] == '\0'){ // Si on a juste appuyé sur entrée on continue
		freeTab(mots, MAX_NB);
		return 1;
	}
	
	int cmdPerso = commandePerso(str, mots, tailleMotCommande);
	freeTab(mots, MAX_NB);
	
	return 1;
		
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
{ // sépare la chaine de caractère en plusieurs mots / On pourrait juste utiliser strtok
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
		else
			printf("Pas assez d'arguments");
	}
	else if(!strcmp("help", mots[0])){
		if(!strcmp("-ts", mots[1])) // Commande d'aide TS
			return helpTS(str, mots, taille);
		else if(!strcmp("-meta", mots[1])) // Commande d'aide Meta
			return helpMeta(str, mots, taille);
		else if(!strcmp("-get", mots[1])) // Commande d'aide Meta
			return helpGet(str, mots, taille);
		else
			printf("Pas assez d'arguments");
	}
	else if(!strcmp("show", mots[0])){
		if(taille > 1 && !strcmp("-i", mots[1])) // Commande d'aide affichage d'un capteur particulier
			return showMetaI(str, mots, taille);
		else if(taille > 1 && !strcmp("-meta", mots[1])) // Commande d'affichage de tous les capteurs
			return showMeta(str, mots, taille);
		else
			printf("Pas assez d'arguments\n");
	}
	else if(!strcmp("get", mots[0])){
		return get(str, mots, taille);
	}
	return 0;

}

int help(char* str, char** mots, int taille){
	
	printf("Liste des commandes :\n");
	printf("*add -ts [time] [Id metadata] [valeur] - Ajoute une timeseries\n");
	printf("*add -meta [id] [nom] [typeCapteur]	[typeDonnees] [unite] [description] - Ajoute une metadata\n");
	printf("*help -ts - Affiche l'aide sur les timeseries\n");
	printf("*help -get - Affiche l'aide sur la commande get\n");
	printf("*help -meta - Affiche l'aide sur les metadata\n");
	printf("*show -meta - Affiche l'ensemble des infos sur les metadatas\n");
	printf("*show -[i] - affiche les infos d'un capteur\n");
	printf("*get [x] [y] [z] [type] [valeur1] [valeur2] [date1] [date2] - Renvoi les timeseries correspondant aux arguments, voir help -get pour plus d'infos\n");
	
	return 1;
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
int helpGet(char* str, char** mots, int taille){
	
	printf("si x = 0, pas de type renseigné \nsi x = 1, prise en compte du type \nsi y = 0, pas de valeurs \nsi y = 1, vérification de l’égalité avec la valeur \n");
	printf("si y = 2, vérification de l’appartenance à l’intervalle des deux valeurs \nsi y = 3, vérification de la non appartenance à l’intervalle des deux valeurs \n");
	printf("si z = 0, pas de date renseignée \nsi z = 1, vérification de l’égalité avec le temps \nsi z = 2, vérification de l’appartenance à l’intervalle des deux temps \n");
	printf("si z = 3, vérification de la non appartenance à l’intervalle des deux temps");
	
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
			fprintf(fichierMeta, "%s| %s |%s |%s |%s |%s\n", mots[2], mots[3], mots[4], mots[5], mots[6], mots[7]); // petit tweak pour avoir un bon affichage
			fclose(fichierMeta);
			return 1;
		}
		else
			printf("Impossible d'ouvrir le fichier Metadata.txt\n");
	}
	return 0;
}

int showMeta(char* str, char** mots, int taille){
	//Affiche les différentes metadata présentes dans l'application
	
	if(taille > 2){
		printf("Trop d'arguments indiqués\n");
		return 0;
	}
	
	char text[MAX];
	const char s[2] = "|";
	char* token;
	
	FILE* fMeta = NULL;
	fMeta = fopen("Metadata.txt", "r");
	
	if(fMeta != NULL){
		while(fgets(text, MAX, fMeta) != NULL){
			token = strtok(text, s);
			while(token != NULL){ // retire les "|" du fichier de save
				printf("%s", token);
				token = strtok(NULL, s);
			}
		}
		fclose(fMeta);
		return 1;
	}
	else
		printf("Aucune metada enregistrée");
	return 0;
}


int showMetaI(char* str, char** mots, int taille){
	//Affiche une metadata en particulier
	
	if(taille > 2){
		printf("Trop d'arguments indiqués\n");
		return 0;
	}
	
	char text[MAX];
	const char s[2] = "|"; // def séparateur
	char* token; // def les sous-chaines
	int indice = stringToInt(mots[taille - 1]); // indice voulu
	
	FILE* fMeta = NULL;
	fMeta = fopen("Metadata.txt", "r");
	if(fMeta != NULL){
		while(fgets(text, MAX, fMeta) != NULL){
			token = strtok(text, s); // découpe la chaine en morceaux
			int indiceActuel = stringToInt(token);
			
			if(indice == indiceActuel){ //vérif de l'indice
				while(token != NULL){ // retire les "|" du fichier de save
					printf("%s", token);
					token = strtok(NULL, s);
				}
			}
		}
		fclose(fMeta);
		return 1;
	}
	else
		printf("Aucune metada enregistrée");
	return 0;
	
}

int get(char* str, char** mots, int taille){
	
	//On récupère les différents éléments de la commande
	int x = stringToInt(mots[1]); // type 0-1 (idMeta)
	int y = stringToInt(mots[2]); // valeur 0-3
	int z = stringToInt(mots[3]); // date 0-3
	int tailleCommande = x + y + z;
	int position = 4;
	int type = 0, val1 = 0, val2 = 0, date1 = 0, date2 = 0;
	int timestamp = 0, idMeta = 0, valeur = 0;
	
	char text[MAX];
	const char s[2] = " "; // def séparateur
	char* token; // def les sous-chaines
	
	//Vérification de la taille de la commande
	if(y == 3)
		tailleCommande--;
	if(z == 3)
		tailleCommande--;
	if(tailleCommande < taille){
		printf("Trop d'arguments\n");
		return 0;
	}
	else if(tailleCommande > taille){
		printf("Pas assez d'arguments\n");
		return 0;
	}
	
	//On récupère les différents élements de la commande
	if(x == 1){
		type = mots[position];
		position++;
	}
	
	if(y > 1){
		val1 = mots[position];
		position++;
		if(y > 2){
			val2 = mots[position];
			position++;
		}
	}
	if(z > 1){
		date1 = mots[position];
		position++;
		if(z > 2){
			date2 = mots[position];
			position++;
		}
	}
	
	
	
	FILE* fTs = NULL;
	fTs = fopen("TimeSeries.txt", "r");
	if(fTs != NULL){
		while(fgets(text, MAX, fTs) != NULL){
			
			/*
			 *Récupérer les 3 valeurs puis faire les comparaisons et renvoyer si c'est bon.
			 */
			timestamp = stringToInt(strtok(text, s)); // découpe la chaine en morceaux
			idMeta = stringToInt(strtok(NULL, s));
			valeur = stringToInt(strtok(NULL, s));
			
			if(idMetaIsOk(x, type, idMeta) && valueIsOk(y, val1, val2, valeur) && timeIsOk(z, date1, date2, timestamp)){
				printf("%d %d %d\n", timestamp, idMeta, valeur);
			}
			
		}
		fclose(fTs);
		return 1;
	}
	else
		printf("Aucune metada enregistrée");
	return 0;
	
	
	
	return 0;
}

int idMetaIsOk(int x, int type, int idMeta){
	//Si la metadata est demandée et qu'elle correspond
	if(x == 0 || type == idMeta)
		return 1;
	return 0;
}

int valueIsOk(int y, int val1, int val2, int valeur){
	//Si la valeur est demandée et qu'elle correspond à ce qui est voulu
	if(y == 0)
		return 1;
	if(y == 1 && valeur == val1)
		return 1;
	if(y == 2 && valeur >= val1 && valeur <= val2) // si val1 <= valeur <= val2
		return 1;
	if(y == 3 && valeur <= val1 || valeur >= val2) // si valeur n'est pas entre val1 et val2
		return 1;
	return 0;

}

int timeIsOk(int z, int date1, int date2, int timestamp){
	//Si le temps est demandée et qu'il correspond à ce qui est voulu
	if(z == 0)
		return 1;
	if(z == 1 && timestamp == date1)
		return 1;
	if(z == 2 && timestamp >= date1 && timestamp <= date2) 
		return 1;
	if(z == 3 && timestamp <= date1 || timestamp >= date2) 
		return 1;
	return 0;
}


int stringToInt(char* str){
	//Transforme un char* en int
	int i = 0, r = 0, p = 1;
	int neg = 0;
	//i = indice pour parcourir la chaine
	// p = variable utilisée pour faire *1/*10/*100.../*x
	// neg variable utilisée pour voir si c'est un nombre négatif
	
	if(str[0] == '-')
		neg++;
		
	for(i = strlen(str)-1; i >= neg; i--){
		r += (str[i] - '0') * p;
		p *= 10;
	}
	
	if(str[0] == '-')
		return -r;
	return r;
	
}

void freeTab(char** str, int taille)
{//libère la mémoire d'un tableau à double dimension de char
	int i;
	for(i = 0; i < taille; i++)
	{
		free(str[i]);
		str[i] = NULL;
	}
	free(str);
	str = NULL;
}