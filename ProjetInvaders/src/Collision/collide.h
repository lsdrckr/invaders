#ifndef __COLLIDE_H__
#define __COLLIDE_H__
#include "../ListeChainee/list.h"

void collide_mstr_missile(cellule** mstr, lutin* miss);
void collide_p_b(cellule** bomb, lutin* play);
void collide(cellule** mstr, lutin* miss, cellule** bomb, lutin* play);

#endif
