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

int main(void){

  chaine ch =NULL;
  ch=creer_chaine_init(copier_int,NULL,detruire_int,compare_int);
  int a =2;
  insert_val(ch,&a);  
  insert_val(ch,&a);
  insert_val(ch,&a);
  insert_val(ch,&a);

  chaine ch2 =NULL;
  ch2=creer_chaine_init(copier_int,NULL,detruire_int,compare_int);
  int b=3;
  insert_val(ch2,&b);  
  insert_val(ch2,&b);
  print_chaine(ch,stdout,afficher_int);
  print_chaine(ch2,stdout,afficher_int);

  chaine chfu=fusion_chaine(&ch,&ch2);
  print_chaine(ch,stdout,afficher_int);
  detruire_chaine(&chfu);
/*
  chaine chaine2=NULL;
  chaine2=creer_chaine_init();
  insert_val(chaine2,6);
  //insert_val(chaine2,7);
  chaine toto=NULL;
  chaine chaine=NULL;
  chaine=creer_chaine_init();
  
  insert_val(chaine,3);
  insert_val(chaine,2);
  //insert_val(chaine2,8);
  if(val_exist(chaine,2)){
    printf("val exist 2 existe dans chaine\n");
  }
  if(!val_exist(chaine,4)){
    printf("val 4 existe pas dans chaine\n");
  }
  toto = fusion_chaine(&chaine,&chaine2);
  print_chaine(toto);
  detruire_chaine(&toto);*/
  return 0;
}
