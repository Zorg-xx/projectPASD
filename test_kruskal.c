#include "kruskal.h"
#include "union_find.h"
#include "liste_simplement_chainee.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

void copier_int(void* val, void** pt)
{
  assert(NULL != val);
  assert(NULL != pt);
  *pt =(int*)malloc(sizeof(int));
  assert(NULL != *pt );
  memcpy(*pt, val, sizeof(int));
  
}

void detruire_int(void** pt){
  assert(NULL != pt);
  if(*pt != NULL){
    free(*pt);
    (*pt)= NULL;
  }
}

int compare_int(void * _a, void* _b){
  assert(NULL != _a);
  assert(NULL != _b);
  int a=*(int *)_a;
  int b=*(int *)_b;
  return a-b;
}

void afficher_int(void* val, FILE* f)
{
  fprintf(f, "%d", *((int*)(val)));
}


int main(int argc, char** argv) {

  argc=argc;
  argv=argv;
  kruskal kru=creer_kruskal(copier_int,detruire_int,compare_int);
  chargement_fichier("graphes/G_10_SOMMETS","arbres/output/A_10_SOMMETS_RES",afficher_int,kru);
  afficher_arbre_complet( kru,stdout,afficher_int);
  afficher_union(get_union(kru),stdout,afficher_int);
  
  detruire_kruskal(&kru);

  kruskal kru1=creer_kruskal(copier_int,detruire_int,compare_int);
  chargement_fichier("graphes/G_200_SOMMETS","arbres/output/A_200_SOMMETS_RES",afficher_int,kru1);
  afficher_arbre_complet( kru1,stdout,afficher_int);
  afficher_union(get_union(kru1),stdout,afficher_int);
  
  detruire_kruskal(&kru1);

  kruskal kru2=creer_kruskal(copier_int,detruire_int,compare_int);
  chargement_fichier("graphes/G_1000_SOMMETS","arbres/output/A_1000_SOMMETS_RES",afficher_int,kru2);
  afficher_arbre_complet( kru2,stdout,afficher_int);
  afficher_union(get_union(kru2),stdout,afficher_int);
  detruire_kruskal(&kru2);

    kruskal kru3=creer_kruskal(copier_int,detruire_int,compare_int);
  chargement_fichier("graphes/G_2500_SOMMETS","arbres/output/A_2500_SOMMETS_RES",afficher_int,kru3);
  afficher_arbre_complet( kru3,stdout,afficher_int);
  afficher_union(get_union(kru3),stdout,afficher_int);
  
  detruire_kruskal(&kru);
  return 0;
}

