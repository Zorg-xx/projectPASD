#ifndef KRUSKAL_H
#define KRUSKAL_H

#include "union_find.h"

#include <stdio.h>
#include <stdlib.h>

/*! \file kruskal.h
 * \brief Exécution de l'algorithme de Kruskal.
 *
 * La sortie de l'algorithme doit être fournie dans un fichier respectant le format suivant : 
 * u v w(u,v)
 * avec u < v, où (u,v) est une arête et w(u,v) le poids de cette arête.
 *
 * \copyright PASD
 * \version 2017
 */

typedef struct kruskal *kruskal;
typedef struct segment *segment;
segment creer_segment(void * _valA,void * _valB,int _poid,void(*copier)(void *,void**),void (*detruire)(void**),int(*compare)(void*,void*));
void afficher_segment(segment a,FILE *out,void (*afficher)(void*,FILE*));
kruskal creer_kruskal(void (*copier)(void*,void**),void (*detruire)(void**),int (*compare)(void*,void*));
void detruire_kruskal(kruskal *kru);
void chargement_fichier(char* fileName,char* fileDest,void(*afficher)(void*,FILE*),kruskal kru);
void afficher_arbre_complet(kruskal kru,FILE *out,void (*afficher)(void*,FILE*));
void afficher_segment(segment a,FILE *out,void (*afficher)(void*,FILE*));
void detruire_segment(segment *seg, void(*detruire)(void**));
void afficher_arbre_min(kruskal kru,FILE *out,void (*afficher)(void*,FILE*));
union_find get_union(kruskal kru);
#endif

