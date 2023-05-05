#include "collide.h"
#include "../Graphique/libgraph.h"
#include "../ListeChainee/list.h"
#include "../define.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>



void collide_mstr_missile(cellule **mstr, lutin *m){
    cellule *tmp = NULL;
    tmp = *mstr;
    
    int taille_mstr[2];
    tailleLutin(tmp->lut.sprite, &taille_mstr[0], &taille_mstr[1]);
    
    int taille_m[2];
    tailleLutin(m->sprite, &taille_m[0], &taille_m[1]);
    
    bool cont = 1;
    while ((tmp != NULL) && (cont)){
        if ((tmp->lut.posx <= m->posx) && ((tmp->lut.posx + taille_mstr[0]) >= (m->posx + taille_m[0])) && (tmp->lut.posy <= m->posy) && ((tmp->lut.posy + taille_mstr[1]) >= (m->posy + taille_m[1]))){
            m->posy = -100;
            tmp->lut.etat = 0;
            printf("BOOM\n");
            cont = 0;
        }
        tmp = tmp->suivant;
    }
}

void collide(cellule **mstr, lutin *m/*, cellule **b, lutin *p*/){
    collide_mstr_missile(mstr, m);
}
