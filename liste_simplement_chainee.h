#ifndef LISTE_SIMPLEMENT_CHAINEE_H
#define LISTE_SIMPLEMENT_CHAINEE_H
#include <stdio.h>
#include <stdlib.h>
typedef struct liste_chaine *chaine;
chaine creer_chaine_init(void (*copier)(void*,void**),int (*val_exist)(void*,void*),void (*detruire)(void**),int (*compare)(void*,void*));
void print_chaine(chaine chaine,FILE *out, void(*afficher)(void*_val,FILE *out));
void insert_val(chaine chaine,void* val);
void detruire_chaine(chaine *chaine); 
int val_exist(chaine chaine,int a);
chaine fusion_chaine(chaine *ch1, chaine *ch2);
void detruire_chaine_simple(chaine *chaine);
int compare_taille(chaine chaine1,chaine chaine2);

/*----------fonction complémentaire pour les test--------------*/
void getrang(chaine ch);

void isNull(chaine link);
#endif
