#include "liste_simplement_chainee.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


/*! Un maillon est un pointeur sur (référence vers) une struct maillon_struct . */
typedef struct maillon_struct *maillon;

/*!
 * Structure servant à définir un élément de type int de la liste.
 * Cette structure n'est visible que depuis listes_int.c .
 * Les fonctions attenantes sont static pour être également masquées. */
struct maillon_struct {
  void* val;
  maillon next;
  maillon racine;
};


struct liste_chaine
{
  unsigned int rang;
  maillon racine;
  void (*copier)(void*,void**);
  int (*val_exist)(void*,void*);
  void (*detruire)(void**);  
};


static maillon creer_maillon(void * _val,void (*copier)(void*,void**)){
  maillon maillon=malloc(sizeof(struct maillon_struct));
  copier(_val,&(maillon->val));
  maillon->val=_val;
  maillon->next=NULL;
  return maillon;
}

chaine creer_chaine_init(){
  chaine chaine=malloc(sizeof(struct liste_chaine));
  chaine->rang=0;
  chaine->racine=NULL;
  return chaine;
}

void insert_val(chaine ch,void* _val){
  maillon mail=creer_maillon(_val,ch->copier);
  maillon courant=ch->racine;
  while(courant!=NULL)
    courant=courant->next;
  courant =mail;
  
}
/*retourne -1 si le rang de la chaine  de gauche est plus grand
 * retourne 1 si le rang de la chaine de  droite est plus grand
 * retourne 0 si les deux rang son égaux 
 */
int compare_taille(chaine chaine1,chaine chaine2){
  if(chaine1->rang > chaine2->rang){
    return -1;
  }else if(chaine1->rang < chaine2->rang){
    return 1;
  }else{
    return 0;
  }
}

static void detruire_maillon_rec(maillon* maillon, void (*detruire)(void ** pt)){
  if((*maillon)!=NULL){
    if((*maillon)->next!=NULL){
      detruire_maillon_rec(&(*maillon)->next,*detruire);
    }
    detruire(&(*maillon)->val);
    detruire((void*) maillon);
  }
}

void detruire_chaine(chaine* ch){
  detruire_maillon_rec(&(*ch)->racine,(*ch)->detruire);
  free((*ch));
}

/*

void print_chaine(chaine chaine){
  assert(chaine!=NULL);
  maillon courant=NULL;
  courant=chaine->racine;
  if(courant==NULL){
    printf("chaine vide\n");
  }else{
    printf("rang de la chaine : %d\n",chaine->rang);
    while(courant!=NULL){
      printf("%d",courant->val);
      if((courant=courant->next))
	printf("->");
      else printf("\n");
    }
  }
}

void insert_val(chaine chaine,int val){
  assert(chaine!=NULL);
  maillon courant = NULL;
  courant =chaine->racine;
  if(courant==NULL){
    chaine->racine=creer_maillon(val);
    chaine->racine->racine=chaine->racine;
  }else{
    while(courant->next!=NULL){
      courant=courant->next;
    }
    chaine->rang+=1;
    courant->next=creer_maillon(val);
    courant->next->racine=chaine->racine;
  }
}


void detruire_chaine(chaine *chaine){
  assert(chaine!=NULL);
  detruire_maillon_rec((*chaine)->racine);
  printf("destruction chaine\n");
  free(*chaine);
}


int val_exist(chaine chaine,int a){
  assert(chaine!=NULL);
  maillon courant=chaine->racine;
  while(courant!=NULL){
    if(courant->val==a){
      return 1;
    }
    courant=courant->next;
  }

  return 0;
}

void detruire_arbre_simple(chaine *chaine){
  assert(chaine!=NULL);
  free(*chaine);
  (*chaine)=NULL;
}

void isNull(chaine link){
  if(link->racine==NULL)
    printf("non\n");
}

//fusion et destuction du plus petit arbre et renvoi l'arbre fusionné
chaine fusion_chaine(chaine* ch1, chaine* ch2){
  assert(ch1!=NULL);
  assert(ch2!=NULL);
  printf("fusion\n");
  if((*ch1)->rang >= (*ch2)->rang){
    maillon courant1=(*ch1)->racine;
    while(courant1->next!=NULL){
      courant1=courant1->next;
    }
    
    courant1->next=(*ch2)->racine;
    while(courant1->next!=NULL){
      courant1->racine=(*ch1)->racine;
      courant1=courant1->next;
      (*ch1)->rang+=1;
    }
    detruire_arbre_simple(ch2);
    return *ch1;
  }else{
    maillon courant2=(*ch2)->racine;
    while(courant2->next!=NULL){
      courant2=courant2->next;
    }
    courant2->next=(*ch1)->racine;
    while(courant2->next!=NULL){
      courant2->racine=(*ch2)->racine;
      courant2=courant2->next;
      (*ch2)->rang+=1;
    }
    detruire_arbre_simple(ch1);
    return *ch2;
    }
}
*/
