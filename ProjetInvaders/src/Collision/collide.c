#include "collide.h"
#include "../Graphique/libgraph.h"
#include "../ListeChainee/list.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void collide_mstr_missile(cellule** mstr, lutin* miss)
{
    cellule* tmp = NULL;
    tmp = *mstr;

    int taille_mstr[2];
    tailleLutin(tmp->lut.sprite, &taille_mstr[0], &taille_mstr[1]);

    int taille_m[2];
    tailleLutin(miss->sprite, &taille_m[0], &taille_m[1]);

    while (tmp != NULL) {
        if ((tmp->lut.posx <= (miss->posx + taille_m[0])) && ((tmp->lut.posx + taille_mstr[0]) >= (miss->posx)) && (tmp->lut.posy <= (miss->posy + taille_m[1])) && ((tmp->lut.posy + taille_mstr[1]) >= miss->posy)) {
            miss->posy = 0 - taille_m[1];
            tmp->lut.etat = 0;
            break;
        }
        tmp = tmp->suivant;
    }
}

void collide_p_b(cellule** bomb, lutin* play)
{
    cellule* tmp = NULL;
    tmp = *bomb;

    int taille_bomb[2];
    tailleLutin(tmp->lut.sprite, &taille_bomb[0], &taille_bomb[1]);

    int taille_p[2];
    tailleLutin(play->sprite, &taille_p[0], &taille_p[1]);

    while (tmp != NULL) {
        if ((tmp->lut.posx <= play->posx + taille_p[0]) && (tmp->lut.posx + taille_bomb[0] >= play->posx) && (tmp->lut.posy <= play->posy + taille_p[1]) && (tmp->lut.posy + taille_bomb[1] >= play->posy)) {
            tail_pop(bomb);
            play->etat = 0;
            break;
        } else
            tmp = tmp->suivant;
    }
}

void collide(cellule** mstr, lutin* miss, cellule** bomb, lutin* play)
{
    collide_mstr_missile(mstr, miss);
    collide_p_b(bomb, play);
}
