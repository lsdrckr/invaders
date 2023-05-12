#include "list.h"
#include "../Graphique/libgraph.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void head_push(cellule** pointL, struct lutin lut)
{
    cellule* tmp = malloc(sizeof(cellule));
    tmp->lut = lut;
    tmp->suivant = *pointL;
    *pointL = tmp;
}

void print_list(cellule* list)
{
    cellule* tmp = NULL;
    tmp = list;
    while (tmp != NULL) {
        printf("(%d;%d) -> ", tmp->lut.posx, tmp->lut.posy);
        tmp = tmp->suivant;
    }
    printf("\n");
}

void head_pop(cellule** pointL)
{
    cellule* tmp = NULL;
    tmp = *pointL;
    *pointL = (*pointL)->suivant;
    free(tmp);
}

cellule** tail_pop(cellule** pointL)
{
    cellule* tmp = NULL;
    tmp = *pointL;
    cellule* list = NULL;
    cellule* tmp2 = NULL;
    while (tmp->suivant->suivant != NULL) {
        tmp = tmp->suivant;
    }
    list = tmp;
    tmp2 = tmp->suivant;
    list->suivant = NULL;
    free(tmp2);
    return pointL;
}

void monster_pop(cellule** pointL)
{
    cellule* tmp = *pointL;
    cellule* ptmp = NULL;
    while (tmp != NULL) {
        if (tmp->lut.etat == 0) {
            if (ptmp == NULL) {
                *pointL = tmp->suivant;
            } else {
                ptmp->suivant = tmp->suivant;
            }
            cellule* tmp2 = tmp;
            tmp = tmp->suivant;
            free(tmp2);
        } else {
            ptmp = tmp;
            tmp = tmp->suivant;
        }
    }
    free(tmp);
}

void free_list(cellule** pointL)
{
    while ((*pointL)->suivant != NULL) {
        head_pop(pointL);
    }
    head_pop(pointL);
}

void init_list_monster(cellule** pointL, int n_x, int n_y, int ecart, int sprt, int bord)
{
    for (int cmpty = 0; cmpty < n_y; cmpty++) {
        for (int cmptx = 0; cmptx < n_x; cmptx++) {
            lutin lut;
            lut.sprite = sprt;
            lut.posx = ecart * cmptx + bord + 20;
            lut.posy = ecart * cmpty + bord + 20;
            lut.etat = 1;
            head_push(pointL, lut);
            afficherLutin(lut.sprite, lut.posx, lut.posy);
            majSurface();
        }
    }
}

void bomb_add(cellule** pointL, int x_p, int y_p, int sprt)
{
    lutin lut;
    lut.posx = x_p;
    lut.posy = y_p;
    lut.sprite = sprt;
    lut.etat = 1;
    head_push(pointL, lut);
    afficherLutin(lut.sprite, lut.posx, lut.posy);
}
