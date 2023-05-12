#include "Collision/collide.h"
#include "Deplacement/move.h"
#include "Graphique/libgraph.h"
#include "ListeChainee/list.h"
#include "Random/alea.h"

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

#define HAUTEUR 1000 // Hauteur de l'écran
#define LARGEUR 1400 // Largeur de l'écran
#define BORD 0 // Distance entre le bord de l'écran et les monstres
#define COL 9 // Nombres de colonnes de monstres
#define LIN 3 // Nombres de lignes de monstres
#define ECART 70 // Distance entre chaque monstres
#define BOMBSPEED 50 // Fréquence de tir des bombes
#define MISSILESPEED 25 // Fréquence de tir des missiles
#define VITXP 5 // Vitesse du joueur sur l'axe X
#define SLEEP 10000 // Fréquence de rafrâîchissement
#define HAUTEURP (HAUTEUR - 50) // Hauteur du joueur

// Variables globales
int player1;
int monster1;
// int monster2;
int bombsprt;
int missile;

void init_player(lutin* player, int x_p, int y_p, int sprt)
{
    player->posx = x_p;
    player->posy = y_p;
    player->sprite = sprt;
    player->etat = 1;
}

void init_missile(lutin* missile, int x_m, int y_m, int sprt)
{
    missile->posx = x_m;
    missile->posy = y_m;
    missile->sprite = sprt;
    missile->etat = 1;
    afficherLutin(sprt, x_m, y_m);
}

int cmpt_bas(cellule** pointL)
{
    int cmpt = 0;
    cellule* tmp = NULL;
    tmp = *pointL;
    while (tmp != NULL) {
        int cmpta = 0;
        int cmptb = 0;
        tailleLutin(tmp->lut.sprite, &cmpta, &cmptb);
        if (tmp->lut.posy == bord_bas(tmp) - cmptb) {
            tmp->lut.etat = 2;
            cmpt++;
        }
        tmp = tmp->suivant;
    }
    return cmpt;
}

void del_bomb(cellule** bomb)
{
    cellule** tmp = NULL;
    tmp = bomb;
    while ((*tmp)->suivant != NULL) {
        if (!((*tmp)->lut.posy >= HAUTEUR)) {
            (*tmp) = (*tmp)->suivant;
        }
        else {
            tmp = tail_pop(tmp);
            break;
        }
    }
}

void refresh(cellule* list, cellule* bomb, lutin miss, lutin play)
{
    // Refresh écran
    rectanglePlein(0, 0, LARGEUR, HAUTEUR, 1);

    // Refresh ennemis
    cellule* tmpmstr = NULL;
    tmpmstr = list;

    while (tmpmstr != NULL) {
        afficherLutin(tmpmstr->lut.sprite, tmpmstr->lut.posx, tmpmstr->lut.posy);
        tmpmstr = tmpmstr->suivant;
    }

    // Refresh player
    afficherLutin(play.sprite, play.posx, play.posy);

    // Refresh bombes
    cellule* tmpbomb = NULL;
    tmpbomb = bomb;

    while (tmpbomb != NULL) {
        afficherLutin(tmpbomb->lut.sprite, tmpbomb->lut.posx, tmpbomb->lut.posy);
        tmpbomb = tmpbomb->suivant;
    }

    del_bomb(&bomb);

    // Refresh missile
    afficherLutin(miss.sprite, miss.posx, miss.posy);
}

int bomber(cellule* list, int cmpt)
{
    int taille[2];
    tailleLutin(list->lut.sprite, &taille[0], &taille[1]);
    cellule* tmp = NULL;
    tmp = list;
    int x_b = 0;
    if (tmp != NULL) x_b = tmp->lut.posy + taille[1]/2;
    bool cont = 1;
    while ((tmp != NULL) && (cont)) {
        if (tmp->lut.etat == 2) {
            if (!hasard(0, cmpt)) {
                x_b = tmp->lut.posx + taille[1]/2;
                cont = 0;
            }
            cmpt--;
        }
        tmp = tmp->suivant;
    }
    return x_b;
}

void jeu(lutin* play, cellule* list, cellule* bomb, lutin* miss)
{
    int goo = 1;
    int vitx = 1;
    int tick = 0;
    int vie = 5;

    int taille[2];
    tailleLutin(play->sprite, &taille[0], &taille[1]);

    while (goo) {
        SDL_Event event;
        SDL_PollEvent(&event);

        switch (event.type) {
        case SDL_QUIT:
            goo = 0;
            break;
        case SDL_KEYDOWN:
            if ((event.key.keysym.sym == SDLK_RIGHT) || (event.key.keysym.sym == SDLK_d)) {
                if (play->posx < LARGEUR - BORD - taille[0]) {
                    play->posx += VITXP;
                }
            }

            if ((event.key.keysym.sym == SDLK_LEFT) || (event.key.keysym.sym == SDLK_q)) {
                if (play->posx > BORD) {
                    play->posx -= VITXP;
                }
            }

            if ((event.key.keysym.sym == SDLK_SPACE) && (tick % MISSILESPEED) && (miss->posy <= 0)) {
                init_missile(miss, play->posx + (int)(taille[0] / 2) - 4, play->posy, missile);
            }

            break;
        }

        if (tick % BOMBSPEED == 0) {
            bomb_add(&bomb, bomber(list, cmpt_bas(&list)), bord_bas(list), bombsprt);
        }

        usleep(SLEEP);
        refresh(list, bomb, *miss, *play);
        vitx = move(&list, &bomb, miss, vitx);
        SDL_Delay(1);

        // Collision
        collide(&list, miss, &bomb, play);
        monster_pop(&list);

        if (play->etat == 0) {
            play->etat = 1;
            vie--;
        }

        if ((vie == 0) || (bord_bas(list) >= HAUTEURP)) {
            printf("GAME OVER !\n");
            break;
        }

        if (list == NULL){
            printf("VOUS AVEZ GAGNE !\n");
            break;
        }

        tick++;
    }
}

void init(lutin* player, int x_p, int y_p, int sprtplr, cellule** pointL, int n_x, int n_y, int ecart, int sprtmstr, int bord)
{
    // Initialisation joueur
    init_player(player, x_p, y_p, sprtplr);
    afficherLutin(player->sprite, player->posx, player->posy);

    // Initialisation monstre
    init_list_monster(pointL, n_x, n_y, ecart, sprtmstr, bord);
}

int main(void)
{
    initialise_rand();

    creerSurface(LARGEUR, HAUTEUR, "Space Invader");

    cellule* list = NULL;
    cellule* bomb = NULL;
    lutin miss;
    miss.posy = -1;
    lutin play;

    player1 = chargerLutin("../Lutins/invader_canon.bmp", 0);
    monster1 = chargerLutin("../Lutins/invader_monstre2_1.bmp", 0);
    // monster2 = chargerLutin("../Lutins/invader_monstre2_2.bmp",0);
    bombsprt = chargerLutin("../Lutins/invader_bombe.bmp", 0);
    missile = chargerLutin("../Lutins/invader_missile.bmp", 1);

    init(&play, LARGEUR / 2, HAUTEURP, player1, &list, COL, LIN, ECART, monster1, BORD);

    jeu(&play, list, bomb, &miss);

    fermerSurface();

    return 0;
}
