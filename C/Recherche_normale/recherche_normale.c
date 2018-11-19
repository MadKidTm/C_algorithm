#include <stdio.h>
#include <stdlib.h>
#define TAILLE 10

int recherche(int *tab, int taille, int valeur){
  int i = 0;

  while(i < taille) {
    if(tab[i] == valeur)
      return i;
    else
      i++;
  }

  return -1;
}

int main (){

  int taille = TAILLE;
  int tab[TAILLE]={1,42,35,95,48,15,78,16,65,8};
  int resultat;

  resultat = recherche(tab, taille, 95);

  if (resultat == -1)
    printf("Element non trouvée");
  else
    printf("resultat = %d\n", resultat);

  return 0;
}
