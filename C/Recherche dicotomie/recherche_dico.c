#include <stdio.h>
#include <stdlib.h>
#define TAILLE 10


int rechercheDico(int *tab, int debut, int fin, int valeur){

  int milieu = (debut + fin) / 2;
  printf("milieu = %d \n", milieu);

  if(debut == milieu){

    if(tab[debut] == valeur)
      return milieu;
    else
      return -1;
  }



  if(valeur <= tab[milieu]){
    rechercheDico(tab, debut, milieu, valeur);
    //printf("debut = %d \n milieu = %d", debut, milieu);
  }
  else
    rechercheDico(tab, milieu+1, fin, valeur);
    //printf("fin = %d \n milieu = %d", fin, milieu);

}

int main(void){
  
  
  int tab[TAILLE] = { 1 , 3 , 6 , 9 , 10 , 15 , 16, 23, 25, 30};
  int resultat;

  resultat = rechercheDico(tab, 0, TAILLE, 15);

  printf("resultat = %d \n", resultat);

  return 0;
}
