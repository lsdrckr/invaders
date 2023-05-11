#include "move.h"
#include "../Graphique/libgraph.h"
#include "../ListeChainee/list.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define LARGEUR 1400    //Largeur de l'écran
#define BORD 0          //Distance entre le bord de l'écran et les monstres
#define VITXM 1         //Vitesse des monstres sur l'axe X
#define VITYM 10        //Vitesse des monstres sur l'axe Y
#define VITYB 5         //Vitesse des bombes
#define VITYMISS -15    //Vitesse des missiles


int bord_gauche(cellule* l)
{
    cellule* tmp = NULL;
    tmp = l;
    int min = LARGEUR;
    while (tmp != NULL) {
        if (tmp->lut.posx < min) {
            min = tmp->lut.posx;
        }
        tmp = tmp->suivant;
    }
    return min;
}

int bord_droit(cellule* l)
{
    cellule* tmp = NULL;
    tmp = l;
    int max = 0;
    while (tmp != NULL) {
        int a = 0;
        int b = 0;
        tailleLutin(tmp->lut.sprite, &a, &b);
        if (tmp->lut.posx + a > max) {
            max = tmp->lut.posx + a;
        }
        tmp = tmp->suivant;
    }
    return max;
}

int bord_bas(cellule* l)
{
    cellule* tmp = NULL;
    tmp = l;
    int max = tmp->lut.posy;
    while (tmp != NULL) {
        int a = 0;
        int b = 0;
        tailleLutin(tmp->lut.sprite, &a, &b);
        if (tmp->lut.posy + b > max) {
            max = tmp->lut.posy + b;
        }
        tmp = tmp->suivant;
    }
    return max;
}

void move_mstr(cellule** pL, int dx, int dy)
{
    cellule* p = NULL;
    p = *pL;
    while (p != NULL) {
        p->lut.posx += dx;
        p->lut.posy += dy;
        p = p->suivant;
    }
    majSurface();
}

void move_bomb(cellule** pL, int dy)
{
    cellule* p = NULL;
    p = *pL;
    while (p != NULL) {
        p->lut.posy += dy;
        p = p->suivant;
    }
    majSurface();
}

int move(cellule** pL, cellule** pB, lutin* m, int vitx)
{
    if (bord_gauche(*pL) >= BORD && bord_droit(*pL) <= LARGEUR - BORD) {
        if (vitx == 1) {
            move_mstr(pL, VITXM, 0);
        } else {
            move_mstr(pL, -1 * VITXM, 0);
        }
    }

    else if (bord_gauche(*pL) < BORD) {
        vitx = 1;
        move_mstr(pL, VITXM, VITYM);
    }

    else if (bord_droit(*pL) > LARGEUR - BORD) {
        vitx = -1;
        move_mstr(pL, -1 * VITXM, VITYM);
    }

    move_bomb(pB, VITYB);

    m->posy += VITYMISS;

    return vitx;
}
