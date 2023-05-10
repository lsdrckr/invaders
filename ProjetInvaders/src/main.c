#include "Collision/collide.h"
#include "Deplacement/move.h"
#include "Graphique/libgraph.h"
#include "ListeChainee/list.h"
#include "Random/alea.h"
#include "define.h"
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

// Variables globales
int player1;
int monster1;
// int monster2;
int bomb;
int missile;
int vie;

void init_player(lutin* player, int x, int y, int sprt)
{
    player->posx = x;
    player->posy = y;
    player->sprite = sprt;
    player->etat = 1;
    afficherLutin(sprt, x, y);
}

void init_missile(lutin* missile, int x, int y, int sprt)
{
    missile->posx = x;
    missile->posy = y;
    missile->sprite = sprt;
    missile->etat = 1;
    afficherLutin(sprt, x, y);
}

int cmpt_bas(cellule** pL)
{
    int i = 0;
    cellule* p = NULL;
    p = *pL;
    while (p != NULL) {
        int a = 0;
        int b = 0;
        tailleLutin(p->lut.sprite, &a, &b);
        if (p->lut.posy == bord_bas(p) - b) {
            p->lut.etat = 2;
            i++;
        }
        p = p->suivant;
    }
    return i;
}

void del_bomb(cellule** b)
{
    cellule** tmp = NULL;
    tmp = b;
    while ((*tmp)->suivant != NULL) {
        if ((*tmp)->lut.posy >= HAUTEUR) {
            tmp = tail_pop(tmp);
            break;
        } else {
            (*tmp) = (*tmp)->suivant;
        }
    }
}

void refresh(cellule* l, cellule* b, lutin m, lutin p)
{
    // Refresh écran
    rectanglePlein(0, 0, LARGEUR, HAUTEUR, 1);

    // Refresh ennemis
    cellule* tmpmstr = NULL;
    tmpmstr = l;

    while (tmpmstr != NULL) {
        afficherLutin(tmpmstr->lut.sprite, tmpmstr->lut.posx, tmpmstr->lut.posy);
        tmpmstr = tmpmstr->suivant;
    }

    // Refresh player
    afficherLutin(p.sprite, p.posx, p.posy);

    // Refresh bombes
    cellule* tmpbomb = NULL;
    tmpbomb = b;

    while (tmpbomb != NULL) {
        afficherLutin(tmpbomb->lut.sprite, tmpbomb->lut.posx, tmpbomb->lut.posy);
        tmpbomb = tmpbomb->suivant;
    }

    del_bomb(&b);

    // Refresh missile
    afficherLutin(m.sprite, m.posx, m.posy);
}

int bomber(cellule* l, int cmpt)
{
    cellule* tmp = NULL;
    tmp = l;
    int x = 0;
    bool cont = 1;
    while ((tmp != NULL) && (cont)) {
        if (tmp->lut.etat == 2) {
            if (!hasard(0, cmpt)) {
                x = tmp->lut.posx;
                cont = 0;
            }
            cmpt--;
        }
        tmp = tmp->suivant;
    }
    return x;
}

void jeu(lutin* p, cellule* l, cellule* b, lutin* m)
{
    int go = 1;
    int vitx = 1;
    int tick = 0;

    int taille[2];
    tailleLutin(p->sprite, &taille[0], &taille[1]);

    while (go) {
        SDL_Event event;
        SDL_PollEvent(&event);

        switch (event.type) {
        case SDL_QUIT:
            go = 0;
            break;
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_RIGHT) {
                if (p->posx < LARGEUR - BORD - taille[0]) {
                    p->posx += VITXP;
                }
            }

            if (event.key.keysym.sym == SDLK_LEFT) {
                if (p->posx > BORD) {
                    p->posx -= VITXP;
                }
            }

            if ((event.key.keysym.sym == SDLK_SPACE) && (tick % MISSILESPEED) && (m->posy <= 0)) {
                init_missile(m, p->posx + (int)(taille[0] / 2) - 4, p->posy, missile);
            }

            break;
        }

        if (tick % BOMBSPEED == 0) {
            bomb_add(&b, bomber(l, cmpt_bas(&l)), bord_bas(l), bomb);
        }

        usleep(SLEEP);
        refresh(l, b, *m, *p);
        vitx = move(&l, &b, m, vitx);
        SDL_Delay(1);

        // Collision
        collide(&l, m, &b, p);
        monster_pop(&l);

        if (p->etat == 0) {
            vie --;
            if (vie == 0){
                printf("GAME OVER !");
                vie ++;
            }
            p->etat = 0;
            go = 0;
        }

        tick++;
    }
}

void init(lutin* player, int x, int y, int sprtplr, cellule** pL, int nx, int ny, int e, int sprtmstr, int bord)
{
    // Initialisation joueur
    init_player(player, x, y, sprtplr);

    // Initialisation monstre
    init_list_monster(pL, nx, ny, e, sprtmstr, bord);
}

void end()
{
    rectanglePlein(0, 0, LARGEUR, HAUTEUR, 1);
    int game_over = lutinTexte("GAME OVER !!!", 0);

    //   int taille[2];
    //   tailleLutin(game_over.sprite, &taille[0], &taille[1]);

    afficherLutin(game_over, LARGEUR / 2 /* - taille[0]/2*/, HAUTEUR / 2 /* - taille[1]/2*/);
}

int main(void)
{
    initialise_rand();

    creerSurface(LARGEUR, HAUTEUR, "Space Invader");

    cellule* l = NULL;
    cellule* b = NULL;
    lutin m;
    m.posy = -1;
    lutin p;

    player1 = chargerLutin("../Lutins/invader_canon.bmp", 0);
    monster1 = chargerLutin("../Lutins/invader_monstre2_1.bmp", 0);
    // monster2 = chargerLutin("../Lutins/invader_monstre2_2.bmp",0);
    bomb = chargerLutin("../Lutins/invader_bombe.bmp", 0);
    missile = chargerLutin("../Lutins/invader_missile.bmp", 1);

    init(&p, LARGEUR / 2, HAUTEURP, player1, &l, COL, LIN, ECART, monster1, BORD);

    jeu(&p, l, b, &m);

    // free_list(&l);
    // free_list(&b);

    while (1) {
        end();
    }

    fermerSurface();

    return 0;
}
