#include "union_find.h"
#include "liste_simplement_chainee.h"
//#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
typedef struct sous_ensemble *sous_ensemble;
struct sous_ensemble{
  sous_ensemble root;
  sous_ensemble next;
  chaine val;
};
struct union_find{
  sous_ensemble root;
  unsigned int taille;
  void (*copier)(void*,void**);
  void (*detruire)(void**);
  int (*compare)(void*,void*);
};

void test_null(void * ok){
  if(ok==NULL)
    printf("NULLLLLLLLLLLL\n");
}
union_find union_find_init(void (*copier)(void*,void**),void (*detruire)(void**),int (*compare)(void*,void*)){
  union_find toreturn =NULL;
  toreturn=malloc(sizeof(struct union_find));
  toreturn->compare=compare;
  toreturn->copier=copier;
  toreturn->detruire=detruire;
  toreturn->root=NULL;
  toreturn->taille=0;
  return toreturn;
}

void insert_sous_ensemble_dans_union(union_find unio,void* _val){

  sous_ensemble courant=unio->root;
  if(courant==NULL){
    courant=malloc(sizeof(struct union_find));
    unio->root=courant;
    courant->root=courant;
    courant->next=NULL;
    courant->val=creer_chaine_init(unio->copier,unio->detruire,unio->compare);
    insert_val(courant->val,_val);
  }else{
    while(courant->next!=NULL)
      courant=courant->next;
    courant->next=malloc(sizeof(struct union_find));
    courant->next->next=NULL;
    courant->next->root=unio->root;
    courant->next->val=creer_chaine_init(unio->copier,unio->detruire,unio->compare);
    insert_val(courant->next->val,_val);
  }
  unio->taille++;
}

void afficher_union(union_find unio, FILE *out,void(*afficher)(void* _val, FILE *f)){
  assert(unio!=NULL);
  sous_ensemble sous_ens=unio->root;
  printf("affichage union(s)\n");
    while(sous_ens!=NULL){
      if(sous_ens->val!=NULL)
	print_chaine(sous_ens->val,out,afficher);
      sous_ens=sous_ens->next;
    }
}
sous_ensemble trouver(union_find unio,void* _val){
  if(unio!=NULL && unio->root!=NULL){
    sous_ensemble sous_ens=unio->root;
    while(sous_ens!=NULL){
      chaine test=NULL;
      if(sous_ens->val!=NULL)
	test=val_exist(sous_ens->val,_val);
      if(test!=NULL){
	return sous_ens;
      }
      sous_ens=sous_ens->next;
    }
  }else{
    printf("l'union est NULL\n");
  }
  return NULL;
}

void unifier(sous_ensemble ens1, sous_ensemble ens2){
  fusion_chaine(&(ens1->val),&(ens2->val));
}

static void destruction_ensemble_rec(sous_ensemble *sous_ens){
  if((*sous_ens)!=NULL){
    if((*sous_ens)->next!=NULL){
      destruction_ensemble_rec(&(*sous_ens)->next);
    }
    if((*sous_ens)->val!=NULL)
      detruire_chaine(&(*sous_ens)->val);
    free(*sous_ens);
    (*sous_ens)=NULL;
  }
}
void destruction_union(union_find *unio){
  if(*unio!=NULL){
    if((*unio)->root!=NULL){
      destruction_ensemble_rec(&(*unio)->root);
    }
  free(*unio);
  }
}

