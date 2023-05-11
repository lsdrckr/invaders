#include "collide.h"
#include "../Graphique/libgraph.h"
#include "../ListeChainee/list.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void collide_mstr_missile(cellule** mstr, lutin* m)
{
    cellule* tmp = NULL;
    tmp = *mstr;

    int taille_mstr[2];
    tailleLutin(tmp->lut.sprite, &taille_mstr[0], &taille_mstr[1]);

    int taille_m[2];
    tailleLutin(m->sprite, &taille_m[0], &taille_m[1]);

    bool cont = 1;
    while ((tmp != NULL) && (cont)) {
        if ((tmp->lut.posx <= m->posx) && ((tmp->lut.posx + taille_mstr[0]) >= (m->posx + taille_m[0])) && (tmp->lut.posy <= m->posy) && ((tmp->lut.posy + taille_mstr[1]) >= (m->posy + taille_m[1]))) {
            m->posy = -100;
            tmp->lut.etat = 0;
            cont = 0;
            break;
        }
        tmp = tmp->suivant;
    }
}

void collide_p_b(cellule** bomb, lutin* p)
{
    cellule* tmp = NULL;
    tmp = *bomb;

    int taille_bomb[2];
    tailleLutin(tmp->lut.sprite, &taille_bomb[0], &taille_bomb[1]);

    int taille_p[2];
    tailleLutin(p->sprite, &taille_p[0], &taille_p[1]);

    bool cont = 1;
    while ((tmp != NULL) && (cont)) {
        if ((tmp->lut.posx >= p->posx) && ((tmp->lut.posx + taille_bomb[0]) <= (p->posx + taille_p[0])) && ((tmp->lut.posy + taille_bomb[1]) >= p->posy) && (tmp->lut.posy <= (p->posy + taille_p[1]))) {
            print_list(*bomb);
            head_pop(bomb);
            print_list(*bomb);
            p->etat = 0;
            cont = 0;
            break;
        }
        tmp = tmp->suivant;
    }
}

void collide(cellule** mstr, lutin* m, cellule** b, lutin* p)
{
    collide_mstr_missile(mstr, m);
    collide_p_b(b, p);
}
