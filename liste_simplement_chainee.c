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
  int (*compare)(void*,void*);
};


static maillon creer_maillon(void * _val,void (*copier)(void*,void**)){
  maillon maillon=malloc(sizeof(struct maillon_struct));
  copier(_val,&(maillon->val));
  maillon->val=_val;
  maillon->next=NULL;
  return maillon;
}

chaine creer_chaine_init(void (*copier)(void*,void**),int (*val_exist)(void*,void*),void (*detruire)(void**),int (*compare)(void*,void*)){
  chaine chaine=malloc(sizeof(struct liste_chaine));
  chaine->copier=copier;
  chaine->val_exist=val_exist;
  chaine->detruire=detruire;
  chaine->compare=compare;
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
  courant->racine=ch->racine;
  ch->rang+=1;
  
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

void detruire_chaine_simple(chaine *chaine){
  assert(chaine!=NULL);
  free(*chaine);
  (*chaine)=NULL;
}

void detruire_chaine(chaine* ch){
  detruire_maillon_rec(&(*ch)->racine,(*ch)->detruire);
  detruire_chaine_simple(ch);
}

static void print_maillon(maillon mail,FILE * out, void(*afficher)(void* _val,FILE * out)){
  if(mail!=NULL){
    afficher(mail->val,out);
    if(mail->next!=NULL){
      fprintf(out, "->");
      print_maillon(mail->next,out,afficher);
    }
  }
}
void print_chaine(chaine chaine,FILE *out, void(*afficher)(void*_val,FILE *out)){
  assert(chaine!=NULL);
  print_maillon(chaine->racine,out,afficher);
}

/*----------fonction complémentaire pour les test--------------*/

void getrang(chaine ch){
  printf("rang : %d\n",ch->rang);
}

void isNull(chaine link){
  if(link->racine==NULL)
    printf("la chaine est null\n");
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
    detruire_chaine_simple(ch2);
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
    detruire_chaine_simple(ch1);
    return *ch2;
    }
}

