#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "../Graphique/libgraph.h"

void head_push(cellule **pL, struct lutin lut){
    cellule *tmp = malloc(sizeof(cellule));
    tmp->lut = lut;
    tmp->suivant = *pL;
    *pL = tmp;
}

void print_list(cellule *l){
    cellule *p;
    p = l;
    while (p != NULL){
        printf("(%d;%d) -> ", p->lut.posx, p->lut.posy);
        p = p->suivant;
    }
    printf("\n");
    return;
}

void head_pop(cellule **pL){
    cellule* tmp;
    tmp = *pL;
    *pL = (*pL)->suivant;
    free(tmp);
}

void free_list(cellule **pL){
    while ((*pL)->suivant != NULL){
        head_pop(pL);
    }
    head_pop(pL);
}

void init_list_monster(cellule **pL, int nx, int ny, int e, int sprt, int bord){
    for(int y = 0; y < ny; y++){
        for(int x = 0; x < nx; x++){
            lutin lut;
            lut.sprite = sprt;
            lut.posx = e*x + bord;
            lut.posy = e*y + bord;
            lut.etat = 1;
            head_push(pL,lut);
            afficherLutin(lut.sprite,lut.posx,lut.posy);
            majSurface();
        }
    }
}
