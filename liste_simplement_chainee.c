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
  void (*detruire)(void**);
  int (*compare_val)(void*,void*);
};


static maillon creer_maillon(void * _val,void (*copier)(void*,void**)){
  maillon mail=malloc(sizeof(struct maillon_struct));
  mail->val=NULL;
  copier(_val,&(mail)->val);
  mail->next=NULL;
  return mail;
}

chaine creer_chaine_init(void (*copier)(void*,void**),void (*detruire)(void**),int (*compare_val)(void*,void*)){
  chaine chaine=malloc(sizeof(struct liste_chaine));
  chaine->copier=copier;
  chaine->detruire=detruire;
  chaine->compare_val=compare_val;
  chaine->rang=0;
  chaine->racine=NULL;
  return chaine;
}

void insert_val(chaine ch,void* _val){
  maillon mail=creer_maillon(_val,ch->copier);
  maillon courant=ch->racine;
  if(courant==NULL){
    ch->racine=mail;
    mail->racine=ch->racine;
  }else{
  while(courant->next!=NULL)
    courant=courant->next;
  courant->next=mail;
  mail->racine=ch->racine;
  ch->rang+=1;
  }
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

static int compare_val_maillon(maillon mail,void*val2,int(*compare)(void*val1,void*val2)){
  return compare(mail->val,val2);
}

chaine val_exist(chaine ch, void* _val){
  maillon courant=ch->racine;
  while(courant!=NULL){
    int test = compare_val_maillon(courant,_val,ch->compare_val);
    if(test==0 ){
      return ch;
    }
    courant=courant->next;
  }
  return NULL;
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
  fprintf(out, "\n");
}


int compare_val(void *val1, void*val2, int(*compare)(void*v1,void*v2)){
  
  return compare(val1,val2);
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

