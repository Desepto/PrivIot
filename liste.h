

struct element{
  POINT p;
  struct element* suiv;
};
typedef struct element Element;
typedef Element* Liste;


Liste init_vide();
int estVide(Liste L);
void affiche_liste_recursive(Liste L);
Liste ajoutDebut(Liste l, POINT valeur);
Liste ajoutFin(Liste l, POINT valeur);
Liste supprimer(Liste l, POINT valeur);
int nbElement(Liste l);
int recherche(Liste l, POINT valeur);
void libereListe(Liste l);
