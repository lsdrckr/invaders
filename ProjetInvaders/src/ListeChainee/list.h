#ifndef __LIST_H__
#define __LIST_H__

typedef struct lutin {
    int sprite;
    int posx;
    int posy;
    int etat;
} lutin;

typedef struct cellule {
    struct lutin lut;
    struct cellule* suivant;
} cellule;

void head_push(struct cellule** pointL, struct lutin lut);
void print_list(struct cellule* list);
void head_pop(struct cellule** pointL);
void free_list(struct cellule** pointL);
void init_list_monster(cellule** pointl, int n_x, int n_y, int ecart, int sprt, int bord);
void bomb_add(cellule** pointL, int x_p, int y_p, int sprt);
cellule** tail_pop(cellule** pointL);
void monster_pop(cellule** pointL);

#endif
