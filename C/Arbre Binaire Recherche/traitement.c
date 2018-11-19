#include <stdio.h>
#include <stdlib.h>

struct noeud {
  int val;
  int hauteur;
  struct noeud *filsG;
  struct noeud *filsD;
};

struct maillon {
  struct noeud *adresse;
  struct maillon *suivant;
};

//Procédure d'Affichage en profondeur gauche d'abord avec traitement infixe d'un arbre binaire
//Parametres
// *pointeur sur racine correspondant a la racine de l'arbre binaire
//
void afficherProfondeurGauche(struct noeud *racine){

  if(racine != NULL){
    afficherProfondeurGauche(racine->filsG);
    printf("%d\n", racine->val);
    afficherProfondeurGauche(racine->filsD);
  }
}

//Procédure recursive permettant d'inserer une valeur dans un arbre binaire de recherche
//Parametres
// **racine : pointeur de pointeur sur noeud de la racine de l'arbre
// *noeud : pointeur sur noeud correspondant au nouveau noeud que l'on ajoute
//
void insertionRecursive(struct noeud **racine, struct noeud *noeud){
  if((*racine)->val > noeud->val){
    if((*racine)->filsG == NULL)
      (*racine)->filsG = noeud;
    else{
      insertionRecursive(&(*racine)->filsG, noeud);
    }
  }else{
    if((*racine)->filsD == NULL)
      (*racine)->filsD = noeud;
    else{
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

  if( *racine == NULL){
    *racine = nouveau;
  }else{
    insertionRecursive(racine, nouveau);
  }
}


void enfile(struct maillon **queue, struct maillon **tete, struct noeud *adresse){

  struct maillon *ptr = NULL;
  struct maillon *nouveau;
  nouveau = (struct maillon *)malloc(sizeof(struct maillon));
  nouveau->suivant = NULL;
  nouveau->adresse = adresse;

  printf("valeur enfilé = %d\n", adresse->val);
  if(*queue == NULL){
    *tete = nouveau;
    *queue = nouveau;
  }else{
    ptr = *queue;
    ptr->suivant = nouveau;
    *queue = nouveau;
  }
}

struct noeud *defile(struct maillon **tete, struct maillon **queue){

  struct maillon *ptr;

  if(*tete == NULL){
    return NULL;
  }else{
    ptr = *tete;
    *tete = ptr->suivant;

    if(*tete == NULL)
      *queue = NULL;

    printf("valeur défilé = %d\n", ptr->adresse->val);
    return ptr->adresse;
  }
}

void affichageLargeur(struct noeud **racine, struct maillon **tete, struct maillon **queue){

  struct noeud *noeud;
  noeud = *racine;
  enfile(tete, queue, noeud);

  while( noeud != NULL){
    noeud = defile(tete, queue);
    if(noeud != NULL){
      if(noeud->filsG != NULL)
        enfile(queue, tete, noeud->filsG);
      if(noeud->filsD != NULL)
        enfile(queue, tete, noeud->filsD);
    }
  }
}

int hauteur(struct noeud *racine){
  int hauteurGauche;
  int hauteurDroit;
  int hauteurReele;

  if(racine == NULL){
    return -1;
  }else{
    hauteurGauche = hauteur(racine->filsG);
    hauteurDroit = hauteur(racine->filsD);
    hauteurReele = hauteurGauche < hauteurDroit ? hauteurDroit:hauteurGauche;

    racine->hauteur = hauteurReele + 1;

    return racine->hauteur;
  }
}



int main(void){
  struct noeud *racine = NULL;
  struct maillon *tete = NULL;
  struct maillon *queue = NULL;

  insertionArbre(&racine, 5);
  insertionArbre(&racine, 4);
  insertionArbre(&racine, 9);
  insertionArbre(&racine, 7);

  affichageLargeur(&racine, &tete, &queue);
  racine->hauteur = hauteur(racine);


  //printf("%d\n", racine->val);
  //printf("%d\n", racine->filsG->val);
  //printf("%d\n", racine->filsD->val);
  //printf("%d\n", racine->filsD->filsG->val);


  //afficherProfondeurGauche(racine);

  //enfile(&queue, &tete, racine);
  //enfile(&queue, &tete, racine->filsG);
  //enfile(&queue, &tete, racine->filsD);

  //defile(&tete, &queue);
  //defile(&tete, &queue);
  //defile(&tete, &queue);
  return 0;
}
