#ifndef __COLLIDE_H__
#define __COLLIDE_H__
#include "../ListeChainee/list.h"

void collide_mstr_missile(cellule **mstr, lutin *m);
void collide_p_b(cellule **bomb, lutin *p);
void collide(cellule **mstr, lutin *m, cellule **b, lutin *p);

#endif
