#include "move.h"
#include "../Graphique/libgraph.h"
#include "../ListeChainee/list.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define LARGEUR 1400 // Largeur de l'écran
#define BORD 0 // Distance entre le bord de l'écran et les monstres
#define VITXM 1 // Vitesse des monstres sur l'axe X
#define VITYM 10 // Vitesse des monstres sur l'axe Y
#define VITYB 5 // Vitesse des bombes
#define VITYMISS -15 // Vitesse des missiles

int bord_gauche(cellule* list)
{
    cellule* tmp = NULL;
    tmp = list;
    int min = LARGEUR;
    while (tmp != NULL) {
        if (tmp->lut.posx < min) {
            min = tmp->lut.posx;
        }
        tmp = tmp->suivant;
    }
    return min;
}

int bord_droit(cellule* list)
{
    cellule* tmp = NULL;
    tmp = list;
    int max = 0;
    while (tmp != NULL) {
        int cmpta = 0;
        int cmptb = 0;
        tailleLutin(tmp->lut.sprite, &cmpta, &cmptb);
        if (tmp->lut.posx + cmpta > max) {
            max = tmp->lut.posx + cmpta;
        }
        tmp = tmp->suivant;
    }
    return max;
}

int bord_bas(cellule* list)
{
    cellule* tmp = NULL;
    tmp = list;
    int max = 0;
    while (tmp != NULL) {
        int cmpta = 0;
        int cmptb = 0;
        tailleLutin(tmp->lut.sprite, &cmpta, &cmptb);
        if (tmp->lut.posy + cmptb > max) {
            max = tmp->lut.posy + cmptb;
        }
        tmp = tmp->suivant;
    }
    return max;
}

void move_mstr(cellule** pointL, int d_x, int d_y)
{
    cellule* tmp = NULL;
    tmp = *pointL;
    while (tmp != NULL) {
        tmp->lut.posx += d_x;
        tmp->lut.posy += d_y;
        tmp = tmp->suivant;
    }
    majSurface();
}

void move_bomb(cellule** pointL, int d_y)
{
    cellule* tmp = NULL;
    tmp = *pointL;
    while (tmp != NULL) {
        tmp->lut.posy += d_y;
        tmp = tmp->suivant;
    }
    majSurface();
}

int move(cellule** pointL, cellule** pointB, lutin* miss, int vitx)
{
    if (bord_gauche(*pointL) >= BORD && bord_droit(*pointL) <= LARGEUR - BORD) {
        if (vitx == 1) {
            move_mstr(pointL, VITXM, 0);
        } else {
            move_mstr(pointL, -1 * VITXM, 0);
        }
    }

    else if (bord_gauche(*pointL) < BORD) {
        vitx = 1;
        move_mstr(pointL, VITXM, VITYM);
    }

    else if (bord_droit(*pointL) > LARGEUR - BORD) {
        vitx = -1;
        move_mstr(pointL, -1 * VITXM, VITYM);
    }

    move_bomb(pointB, VITYB);

    miss->posy += VITYMISS;

    return vitx;
}
