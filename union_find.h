#ifndef UNION_FIND_H
#define UNION_FIND_H

/*! \file union_find.h
 * \brief Implémentation de la structure de données Union-Find.
 *
 *
 * \copyright PASD
 * \version 2017
 */

#include <stdio.h>
typedef struct union_find *union_find;
typedef struct sous_ensemble *sous_ensemble;
union_find union_find_init(void (*copier)(void*,void**),void (*detruire)(void**),int (*compare)(void*,void*));
void insert_sous_ensemble_dans_union(union_find unio,void* _val);
void afficher_union(union_find unio, FILE *out,void(*afficher)(void* _val, FILE *f));
sous_ensemble trouve(union_find unio,void* _val);
void fusion(sous_ensemble ens1, sous_ensemble ens2);
void destruction_union(union_find *unio);
#endif
