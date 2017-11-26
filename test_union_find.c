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
  union_find unio=union_find_init(copier_int,detruire_int,compare_int);
  int tab[]={1,2,3,4};
  insert_sous_ensemble_dans_union(unio,&tab[1]);
  insert_sous_ensemble_dans_union(unio,&tab[2]);
  insert_sous_ensemble_dans_union(unio,&tab[3]);
  sous_ensemble sous_ens=NULL;
  sous_ens=trouver(unio,&tab[2]);
  if(sous_ens==NULL)
    printf("NULLLL\n");
  unifier(trouve(unio,&tab[2]), trouve(unio,&tab[3]));
  afficher_union(unio,stdout,afficher_int);
  destruction_union(&unio);
  return 0;

}

