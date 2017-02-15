#include "listeTs.h"


ListeTs init_vide()
{
	return NULL;
}

int estVide(ListeTs L)
{
	return L == NULL;
}

void affiche_liste_recursive(ListeTs L)
{
	if(!estVide(L))
	{
		printf("Time : %d | IdMeta : %d | Valeur : %d \n", L->t.timestamp, L->t.idMeta, L->t.valeur);
		affiche_liste_recursive(L->suiv);
		
	}	
	
	else
		printf("La liste est vide\n");
}

ListeTs ajoutDebut(ListeTs l, TS valeur)
{
  ListeTs pElt = malloc(sizeof(ListeTs)); 
  pElt->t.timestamp = valeur.timestamp;
  pElt->t.idMeta = valeur.idMeta;
  pElt->t.valeur = valeur.valeur;
  pElt->suiv = l;
  
  return pElt;
}

ListeTs ajoutFin(ListeTs l, TS valeur)
{
	if(estVide(l)) 
		l = ajoutDebut(l, valeur);
	else
		l->suiv = ajoutFin(l->suiv, valeur);
  return l;
}

ListeTs supprimer(ListeTs l, TS valeur)
{
 ListeTs tmp;
  if(estVide(l)) return l;
  else if(l->t.timestamp == valeur.timestamp && l->t.idMeta == valeur.idMeta && l->t.valeur == valeur.valeur){
    tmp = l->suiv;
    free(l);
    return tmp;
  } 
  else{
    l->suiv = supprimer(l->suiv, valeur);
    return l;
  } 
}

int nbElement(ListeTs l)
{
  if(estVide(l)) return 0;
  else return 1 + nbElement(l->suiv);
}

int rechercheTroisAttr(ListeTs l, TS valeur)
{
  if(estVide(l)) return 0;
  else if(l->t.timestamp == valeur.timestamp && l->t.idMeta == valeur.idMeta && l->t.valeur == valeur.valeur) return 1;
  else return rechercheTroisAttr(l->suiv, valeur);
}

void libereListe(ListeTs l)
{
  if(!estVide(l)){
    libereListe(l->suiv);
    free(l);
  }
}

