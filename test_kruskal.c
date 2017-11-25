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

  return 0;
}

