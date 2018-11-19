#include <stdlib.h>
#include <stdio.h>

struct maillon{
  int val;
  struct maillon *suivant;
};

void afficherListeChainee(struct maillon *tete){

  struct maillon *ptr = tete;
  int i = 1;

  while(ptr != NULL){
    printf("case %d = %d\n", i , ptr->val);

    ptr = ptr->suivant;
    i++;
  }

}

void insererEnTete(struct maillon **tete, int val){

  struct maillon *nouveau;
  struct maillon suivant;
  nouveau = (struct maillon *)malloc(sizeof(struct maillon));
  nouveau->val = val;

  if( *tete == NULL){
    *tete = nouveau;
  }
  else{
    nouveau->suivant = *tete;
    *tete = nouveau;
  }
}

void supprimerElement(struct maillon **tete, int val){

  struct maillon *ptr;
  struct maillon *precedent;

  //On verifie que la liste n'est pas vide
  if( *tete != NULL){
    ptr = *tete;

    //On verifie que le maillon ne se trouve pas en debut de chaine
    if(ptr->val == val){
      *tete = ptr->suivant;
      free(ptr);
    //Si ce n'est pas le cas on parcourt la chaine a la recherche du maillon contenant la valeur
    }else{

      while(ptr->suivant != NULL && ptr->val != val){
        precedent = ptr;
        ptr = ptr->suivant;
      }

      //On verifie si on sors de la boucle car on a trouvé la bonne valeur
      if(ptr->val == val){
        //Si le maillon est en fin de chaine on fait pointer le precedent sur NULL
        if(ptr->suivant == NULL){
          free(ptr);
          precedent->suivant = NULL;
        //Si c'est en entre deux maillons on fait pointer le precedent sur le suivant
        }else{
          precedent->suivant = ptr->suivant;
          free(ptr);
        }
      }else{
        printf("La valeur n'as pas été trouvée \n");
      }
    }
  }
}

void insererTri(struct maillon **tete, int val){

  struct maillon *ptr;
  struct maillon *nouveau;
  nouveau = (struct maillon *)malloc(sizeof(struct maillon));
  nouveau->suivant = NULL;

  if(*tete == NULL){
    *tete = nouveau;
  }else{
    *tete = ptr;

    if (ptr->val > val){
      *tete=nouveau;
      nouveau->suivant = ptr;
    }else{
      while(ptr->suivant == NULL && ptr->suivant->val > val){
        ptr = ptr->suivant;
      }

      if(ptr->suivant == NULL)
        ptr->suivant == nouveau;
      else{
        nouveau->suivant = ptr->suivant;
        ptr->suivant = nouveau;
      }
    }
  }
}


int main(void){
  struct maillon *tete = NULL;

  insererEnTete(&tete, 15);
  insererEnTete(&tete, 8);
  insererEnTete(&tete, 5);

  afficherListeChainee(tete);

  insererTri(&tete, 4);

  afficherListeChainee(tete);

}
