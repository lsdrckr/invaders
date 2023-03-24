#ifndef __LIST_H__
#define __LIST_H__

typedef struct lutin{
    int sprite;
    int posx;
    int posy;
    int etat;
}lutin;

typedef struct cellule{
    struct lutin lut;
    struct cellule *suivant;
}cellule;

void head_push(struct cellule **pL, struct lutin lut);
void print_list(struct cellule *l);
void head_pop(struct cellule **pL);
void free_list(struct cellule **pL);
void init_liste(cellule **pl, int nx, int ny, int ex, int ey, int sprt);

#endif
