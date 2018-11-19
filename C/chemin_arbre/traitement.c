#include <stdio.h>
#include <stdlib.h>

struct noeud {
  int val;
  struct noeud *pere;
  struct noeud *filsG;
  struct noeud *filsD;
};

struct maillon {
  struct noeud *adresse;
  struct maillon *suivant;
};

void afficherListe(struct maillon *tete){

  while(tete != NULL){
    printf("%d\n", tete->adresse->val);
  }
}


//Procédure permetant d'ajouter en tete d'une liste chainée l'adresse d'un noeud envoyer en parametre
//Parametres:
//  **tete : pointeur de pointeur sur maillon correspondant a l'adresse de la tête de la liste chainée
//  *pointeur sur noeud correspondant a l'adresse du noeud que l'on souhaite ajouter a la liste
//
void enfile(struct maillon **tete, struct noeud *noeud){

  struct maillon *nouveau;
  nouveau = (struct maillon *)malloc(sizeof(struct maillon));
  nouveau->adresse = noeud;
  nouveau->suivant = NULL;

  if(*tete == NULL){
    *tete = nouveau;
  }else{
    nouveau->suivant = *tete;
    *tete = nouveau;
  }

  printf("valeur enfilée : %d\n", (*tete)->adresse->val);
}


void cheminNoeud(struct noeud *noeud, struct maillon **tete){

  while(noeud->pere != NULL){
    enfile(&(*tete), noeud);
    noeud = noeud->pere;
  }
}


//Fonction permetant de recuperer l'element en tête d'une liste chainée
//Parametres:
//  **tete : pointeur de pointeur sur maillon correspondant a l'adresse de la tête de la liste chainée
//retour:
//  retourne un pointeur sur Noeud
//
struct noeud * defile(struct maillon **tete){

  struct maillon *ptr;
  struct noeud *noeud;

  if(*tete == NULL){
    return NULL;
  }else{
    ptr = *tete;
    *tete = ptr->suivant;
  }
  noeud = ptr->adresse;

  free(ptr);

  return noeud;
}


//Procédure recursive permettant d'inserer une valeur dans un arbre binaire de recherche
//Parametres
// **racine : pointeur de pointeur sur noeud de la racine de l'arbre
// *noeud : pointeur sur noeud correspondant au nouveau noeud que l'on ajoute
//
void insertionRecursive(struct noeud **racine, struct noeud *noeud){
  if((*racine)->val > noeud->val){
    if((*racine)->filsG == NULL){
      (*racine)->filsG = noeud;
      (*racine)->filsG->pere = *racine;
    }else{
      insertionRecursive(&(*racine)->filsG, noeud);
    }
  }else{
    if((*racine)->filsD == NULL){
      (*racine)->filsD = noeud;
      (*racine)->filsD->pere = *racine;
    }else{
      insertionRecursive(&(*racine)->filsD, noeud);
    }
  }
}

// Procédure qui crée un nouveau noeud et l'ajoute a un arbre binaire de recherche
// Parametres:
// **racine : pointeur de pointeur sur racine corespondant a la racine de l'arbre binaire
// val : entier correspondant a la valeur contenu dans le noeud qui sera crée
//
void insertionArbre(struct noeud **racine, int val){

  struct noeud *nouveau;
  nouveau = (struct noeud *)malloc(sizeof(struct noeud));
  nouveau->val = val;
  nouveau->filsD = NULL;
  nouveau->filsG = NULL;
  nouveau->pere = NULL;

  if( *racine == NULL){
    *racine = nouveau;
  }else{
    insertionRecursive(racine, nouveau);
  }
}

// Fonction qui a partir de 2 noeud d'un arbre, nous donne le chemin en commun
// entre les deux noeud en renvoyant les adresses des noeud en commun par lesquels ils passent
// Parametres:
//    *noeud1 : pointeur sur noeud correspondant au premier noeud
//    *noeud2 : pointeur sur noeud correspondant au deuxieme noeud
// Retour:
//    pointeur sur maillon correspondant a la liste des adresses des noeuds en commun
//
struct maillon * cheminCommun(struct noeud *noeud1, struct noeud *noeud2){

  struct maillon *tete1 = NULL;
  struct maillon *tete2 = NULL;
  struct maillon *tete3 = NULL;
  struct maillon *nouveau = NULL;

  cheminNoeud(noeud1, &tete1);
  cheminNoeud(noeud2, &tete2);

  while( tete1 != NULL && tete1->adresse == tete2->adresse){
    nouveau = (struct maillon *)malloc(sizeof(sizeof(struct maillon)));
    nouveau->adresse = tete1->adresse;
    nouveau->suivant = tete3;
    tete3 = nouveau;

    tete1 = tete1->suivant;
    tete2 = tete2->suivant;
  }

  return tete3;
}


int main(void){

  struct noeud *racine = NULL;
  struct maillon *tete1 = NULL;
  struct maillon *tete2 = NULL;
  struct maillon *tete3 = NULL;

  insertionArbre(&racine, 6);
  insertionArbre(&racine, 3);
  insertionArbre(&racine, 17);
  insertionArbre(&racine, 13);
  insertionArbre(&racine, 25);
  insertionArbre(&racine, 11);
  insertionArbre(&racine, 7);
  insertionArbre(&racine, 10);
  insertionArbre(&racine, 26);
  insertionArbre(&racine, 23);


  struct noeud *noeud1 = racine->filsD->filsD->filsD;
  struct noeud *noeud2 = racine->filsD->filsD->filsG;

  printf("noeud = %d\n", noeud1->val);


  tete3 = cheminCommun(noeud1, noeud2);

}
