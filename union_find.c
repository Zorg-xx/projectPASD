#include "union_find.h"
#include "liste_simplement_chainee.h"
#include <stdio.h>
#include <stdlib.h>
typedef struct union_find *union_find; 
struct union_find{
  chaine root;
  chaine next;
};

union_find union_find_init(){
  union_find toreturn =NULL;
  toreturn=malloc(sizeof(struct union_find));
  toretun->root=NULL;
  toreturn->next=NULL;
  return toreturn;
}
void creer_ensemble(union_find uni,int val){
  chaine toreturn=NULL;
  toreturn=creer_chaine_init();
  insert_val(toreturn,val);
  if(uni->root==NULL){
    uni->root=toreturn;
  }else{
    chaine courant=uni->root;
    while(courant!=NULL)
      courant=courant->next;
  }
  courant=toretun;
}


int main(){
  union_find uni=NULL;
  return 0;
}
