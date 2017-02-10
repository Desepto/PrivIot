#include "liste.h"


Liste init_vide()
{
	return NULL;
}

int estVide(Liste L)
{
	return L == NULL;
}

void affiche_liste_recursive(Liste L)
{
	if(!estVide(L))
	{
		printf("%d et %d\n", L->p.x, L->p.y);
		affiche_liste_recursive(L->suiv);
		
	}	
	
	else
		printf("La liste est vide\n");
}

Liste ajoutDebut(Liste l, POINT valeur)
{
  Liste pElt = malloc(sizeof(Element)); 
  pElt->p.x = valeur.x;
  pElt->p.y = valeur.y;
  pElt->suiv = l;
  
  return pElt;
}

Liste ajoutFin(Liste l, POINT valeur)
{
	if(estVide(l)) 
		l = ajoutDebut(l, valeur);
	else
		l->suiv = ajoutFin(l->suiv, valeur);
  return l;
}

Liste supprimer(Liste l, POINT valeur)
{
 Liste tmp;
  if(estVide(l)) return l;
  else if(l->p.x == valeur.x && l->p.y == valeur.y){
    tmp = l->suiv;
    free(l);
    return tmp;
  } 
  else{
    l->suiv = supprimer(l->suiv, valeur);
    return l;
  } 
}

int nbElement(Liste l)
{
  if(estVide(l)) return 0;
  else return 1 + nbElement(l->suiv);
}

int recherche(Liste l, POINT valeur)
{
  if(estVide(l)) return 0;
  else if(l->p.x == valeur.x && l->p.y == valeur.y) return 1;
  else return recherche(l->suiv, valeur);
}

void libereListe(Liste l)
{
  if(!estVide(l)){
    libereListe(l->suiv);
    free(l);
  }
}

