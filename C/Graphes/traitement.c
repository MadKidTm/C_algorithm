#include <stdio.h>
#include <stdlib.h>

#define TAILLE 6

struct maillon {
  struct maillon *suivant;
  int val;
};

void enfile(struct maillon **queue, struct maillon **tete, int val){

  struct maillon *ptr = NULL;
  struct maillon *nouveau;
  nouveau = (struct maillon *)malloc(sizeof(struct maillon));
  nouveau->suivant = NULL;
  nouveau->val = val;

  printf("valeur enfilé = %d\n", val);
  if(*queue == NULL){
    *tete = nouveau;
    *queue = nouveau;
  }else{
    ptr = *queue;
    ptr->suivant = nouveau;
    *queue = nouveau;
  }
}

int defile(struct maillon **tete, struct maillon **queue){

  struct maillon *ptr;

  if(*tete == NULL){
    return -1;
  }else{
    ptr = *tete;
    *tete = ptr->suivant;

    if(*tete == NULL)
      *queue = NULL;

    printf("valeur défilé = %d\n", ptr->val);
    return ptr->val;
  }
}

void parcoursCC(int graphe[TAILLE][TAILLE], int sommet, int marques[TAILLE]){
  
  marques[sommet] = 1;
  printf(" %d \n", sommet);

  for(int i = 0; i < TAILLE ; i++){
    if(i != sommet){
      if(graphe[sommet][i] == 1 && marques[i] == 0){
        parcoursCC(graphe, i, marques);
      }
    }
  }
}

void parcoursProfondeur( int graphe[TAILLE][TAILLE], int sommet){
  int *marques = (int*)malloc(TAILLE * sizeof(int));

  for(int i = 0; i < TAILLE ; i++){
    marques[i] = 0; 
  }

  parcoursCC(graphe, sommet, marques);

  for(int i = 0; i < TAILLE; i++){
    if(marques[i] == 0)
      parcoursCC(graphe, i, marques);
  }
}

void parcoursCCL(int graphe[TAILLE][TAILLE], int sommet, int marques[TAILLE], struct maillon **tete, struct maillon **queue){
  int val;
  enfile(tete, queue, sommet);

  while(*tete != NULL){
    val = defile(tete, queue);
    printf("%d ", val);
    
    for( int i = 0; i<TAILLE; i++){
      if(graphe[sommet][i] == 1 && marques[val] != 1){
        enfile(tete, queue, sommet);
        marques[val] = 1;
      }
    }
  }
}

void parcoursLargeur(int graphe[TAILLE][TAILLE], int sommet){
  printf("test");
  int *marques = (int*)malloc(TAILLE * sizeof(int));

  

  for(int i = 0; i < TAILLE ; i++){
    marques[i] = 0; 
  }

  

  struct maillon *tete;
  struct maillon *queue;

  parcoursCCL(graphe, sommet, marques, &tete, &queue);

  for(int i = 0; i < TAILLE; i++){
    if(marques[i] == 0)
      parcoursCCL(graphe, i, marques, &tete, &queue);
  }
}



int main(void){

  printf("test");

  int graphe[TAILLE][TAILLE] = {
    {0,1,1,0,0,0},
    {1,0,1,1,1,0},
    {1,1,0,1,0,0},
    {0,1,1,0,0,0},
    {0,1,0,0,0,1},
    {0,0,0,0,1,0}
  };
  

  // for(int i = 0; i < TAILLE; i++){
  //   for(int j = 0; j < TAILLE; j++){
  //     printf(" %d ",graphe[i][j]);
  //   }
  //   printf("\n");
  // }

  parcoursProfondeur(graphe, 3);
  parcoursLargeur(graphe, 0);

  
}
