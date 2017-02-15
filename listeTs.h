#include <stdio.h>
#include <stdlib.h>

struct ts{
	int timestamp;
	int idMeta;
	int valeur;	
};
typedef struct ts TS;


struct elemTs{
  TS t;
  struct elemTs* suiv;
};
typedef struct elemTs ElemTs;
typedef ElemTs* ListeTs;


ListeTs init_vide();
int estVide(ListeTs L);
void affiche_liste_recursive(ListeTs L);
ListeTs ajoutDebut(ListeTs l, TS valeur);
ListeTs ajoutFin(ListeTs l, TS valeur);
ListeTs supprimer(ListeTs l, TS valeur);
int nbElement(ListeTs l);
int rechercheTroisAttr(ListeTs l, TS valeur);
void libereListe(ListeTs l);