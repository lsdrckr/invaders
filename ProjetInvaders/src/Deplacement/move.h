#ifndef __MOVE_H__
#define __MOVE_H__
#include "../ListeChainee/list.h"

int bord_gauche(cellule* list);
int bord_droit(cellule* list);
int bord_bas(cellule* list);
void move_mstr(cellule** pointL, int d_x, int d_y);
void move_bomb(cellule** pointL, int d_y);
int move(cellule** pointL, cellule** pointB, lutin* miss, int vitx);

#endif
