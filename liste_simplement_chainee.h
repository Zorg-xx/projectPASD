#ifndef LISTE_SIMPLEMENT_CHAINEE_H
#define LISTE_SIMPLEMENT_CHAINEE_H

typedef struct liste_chaine *chaine;
chaine creer_chaine_init();
void print_chaine(chaine chaine);
void insert_val(chaine chaine,void* val);
void detruire_chaine(chaine *chaine); 
int val_exist(chaine chaine,int a);
chaine fusion_chaine(chaine *ch1, chaine *ch2);
void detruire_arbre_simple(chaine *chaine);
#endif
