#include "kruskal.h"
#include "union_find.h"
#include "liste_simplement_chainee.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
typedef struct point *point;
struct point{
  void *val;
  chaine listeAdja;
};

struct segment{
  point pointA;
  point pointB;
  int(*compare)(void*,void*);
  int poid;
};

struct kruskal{
  segment* arbreComplet;
  segment* arbreMin;
  union_find unio;
  int sizeComp;
  int sizeMin;
  void (*copier)(void*,void**);
  void (*detruire)(void**);
  int (*compare)(void*,void*);
};


static point creer_point(void * _val, void(*copier)(void *,void**),void (*detruire)(void**)){
  point p=malloc(sizeof(struct point));
  copier(_val,&(p->val));
  p->listeAdja=creer_chaine_init(copier,detruire,NULL);
  return p;
}


segment creer_segment(void * _valA,void * _valB,int _poid,void(*copier)(void *,void**),void (*detruire)(void**),int(*compare)(void*,void*)){
  segment seg=malloc(sizeof(struct segment));
  if(compare(_valA,_valB)<1){
    seg->pointA=creer_point(_valA,copier,detruire);
    seg->pointB=creer_point(_valB,copier,detruire);
  }else{
      seg->pointB=creer_point(_valA,copier,detruire);
      seg->pointA=creer_point(_valB,copier,detruire);
  }
  seg->poid=_poid;
  seg->compare=compare;
  return seg;
}

void detruire_point(point *p,void (*detruire)(void**)){
  detruire_chaine(&(*p)->listeAdja);
  detruire(&(*p)->val);
  free(*p);
}
void detruire_segment(segment *seg, void(*detruire)(void**)){
  detruire_point(&(*seg)->pointA,detruire);
  detruire_point(&(*seg)->pointB,detruire);
}

kruskal creer_kruskal(void (*copier)(void*,void**),void (*detruire)(void**),int (*compare)(void*,void*)){
  kruskal kru =malloc(sizeof(struct kruskal));
  kru->copier=copier;
  kru->detruire=detruire;
  kru->compare=compare;
  kru->sizeComp=0;
  kru->sizeMin=0;
  kru->unio=NULL;
  kru->arbreComplet=NULL;
  kru->arbreMin=NULL;
  return kru;
}


void afficher_segment(segment a,FILE *out,void (*afficher)(void*,FILE*)){
    afficher(a->pointA->val,out);
    fprintf(out," ");
    afficher(a->pointB->val,out);
    fprintf(out," %d\n",a->poid);
}

void detruire_kruskal(kruskal *kru){
  if((*kru)->arbreComplet!=NULL){
    for(int i=0;i<(*kru)->sizeComp-1;i++){
      if((*kru)->arbreComplet[i]!=NULL){
      detruire_segment(&(*kru)->arbreComplet[i],(*kru)->detruire);
      free((*kru)->arbreComplet[i]);
      }
    }
    free((*kru)->arbreComplet);
  }
  if((*kru)->arbreMin!=NULL){
    /*for(int i=0;i<(*kru)->sizeMin-1;i++){
      printf("destcomp\n");
      if((*kru)->arbreMin[i]!=NULL){
	detruire_segment(&(*kru)->arbreMin[i],(*kru)->detruire);
	free((*kru)->arbreMin[i]);
      }
    }*/
    free((*kru)->arbreMin);
  }
  destruction_union(&(*kru)->unio);
  free(*kru);
}

void afficher_arbre_complet(kruskal kru,FILE *out,void (*afficher)(void*,FILE*)){
  if(kru->arbreComplet!=NULL){
    int i;
    for( i=0; i < kru->sizeComp-1;i++){
      afficher_segment(kru->arbreComplet[i],out,afficher);
      }
  }
}


void afficher_arbre_min(kruskal kru,FILE *out,void (*afficher)(void*,FILE*)){
  int i;
  printf("arbremin\n");
  for(i=0; i < kru->sizeMin;i++){
    afficher_segment(kru->arbreMin[0],out,afficher);
  }
}

int compare_segment(void const* _a,void const *_b){

  segment a=(segment )_a;
  segment b=(segment )_b;
  int poida=a->poid;
  int poidb=b->poid;
  if(poida!=poidb){
    return poida-poidb;
  } else{
    if(a->compare(a->pointA->val,b->pointA->val)!=0){
      return a->compare(a->pointA->val,b->pointA->val);
    }else{
      return a->compare(a->pointB->val,b->pointB->val);
    }
  }
}

void echanger(segment tableau[],int a ,int b){
  segment temp = tableau[a];
    tableau[a] = tableau[b];
    tableau[b] = temp;
}

void quickSort(segment tableau[],int debut ,int fin){

    int gauche = debut-1;
    int droite = fin+1;
    const segment pivot = tableau[debut];

    if(debut >= fin)
      return;

    while(1)
      {
        do droite--; while(compare_segment(tableau[droite],pivot) >0 );
        do gauche++; while(compare_segment(tableau[gauche] , pivot)<0);

        if(gauche < droite)
	  echanger(tableau, gauche, droite);
        else break;
      }
    quickSort(tableau, debut, droite);
    quickSort(tableau, droite+1, fin);
}



void gestion_union(kruskal kru,segment seg,int *incr,FILE *out,void(*afficher)(void*,FILE*f)){
  union_find unio=kru->unio;
  void * valA= seg->pointA->val;
  void * valB=seg->pointB->val;
  sous_ensemble a=trouver(unio,valA);
  sous_ensemble b =trouver(unio,valB);
  if(a==NULL && b==NULL){
    insert_sous_ensemble_dans_union(unio,valA);
    insert_sous_ensemble_dans_union(unio,valB);
    unifier(trouver(unio,valA),trouver(unio,valB));
    afficher_segment(seg,out,afficher);
    //kru->arbreMin[*incr]=seg;
    *incr+=1;
  }else if(a!=NULL && b==NULL){
    insert_sous_ensemble_dans_union(unio,valB);
    unifier(a,trouver(unio,valB));
    //kru->arbreMin[*incr]=seg;
    afficher_segment(seg,out,afficher);
    *incr+=1;
  }else if(a==NULL && b!=NULL){
    insert_sous_ensemble_dans_union(unio,valA);
    unifier(b,trouver(unio,valA));
    afficher_segment(seg,out,afficher);
    // kru->arbreMin[*incr]=seg;
    *incr+=1;
  }else if(a!=b){
    unifier(a,b);
    afficher_segment(seg,out,afficher);
  }
}

union_find get_union(kruskal kru){
  return kru->unio;
}

void chargement_fichier(char* fileName,char* fileDest,void(*afficher)(void*,FILE*),kruskal kru){
  FILE *f=NULL;
  FILE *dest=NULL;
  char* buff=malloc(sizeof(char)*255);
  char * segChar;
  int a,b,poid;
  int i =0;
  
  kru->unio=union_find_init(kru->copier,kru->detruire,kru->compare);
  
  f=fopen(fileName,"r");
  dest=fopen(fileDest,"w");
  printf("chargement du fichier\n");

  while(fgets(buff,255,f)){
    i++;
  }
  
  rewind(f);
  kru->arbreComplet=malloc(sizeof(struct segment)*i);
  kru->sizeComp=i;
  int test =i;
  
  i=0;

  //passe la premiere ligne
  fgets(buff,255,f);

  while((segChar=fgets(buff,255,f))){
    a=atoi(strtok(segChar," "));
    b=atoi(strtok(NULL," "));
    poid=atoi(strtok(NULL," "));
    kru->arbreComplet[i]=creer_segment(&a,&b,poid,kru->copier,kru->detruire,kru->compare);
    i++;
  }
  quickSort(kru->arbreComplet,0,i-1);

  int nbInsert=0;

  for(int o=0;o<test-1;o++)
      gestion_union(kru,kru->arbreComplet[o],&nbInsert,dest,afficher);
  printf("fichier chargé \n");
  fclose(f);
  fclose(dest);
  free(buff);
 
}
