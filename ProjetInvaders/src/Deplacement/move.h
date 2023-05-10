#ifndef __MOVE_H__
#define __MOVE_H__
#include "../ListeChainee/list.h"

int bord_gauche(cellule* l);
int bord_droit(cellule* l);
int bord_bas(cellule* l);
void move_mstr(cellule** pL, int dx, int dy);
void move_bomb(cellule** pL, int dy);
int move(cellule** pL, cellule** pB, lutin* m, int vitx);

#endif
