#include "Graphique/libgraph.h"
#include "ListeChainee/list.h"
#include "Random/alea.h"
#include "Deplacement/move.h"
#include "define.h"
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <math.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>



//Variables globales
int player1;
int monster1;
// int monster2;
int bomb;
int missile;



void init_player(lutin *player, int x, int y, int sprt) {
  player->posx = x;
  player->posy = y;
  player->sprite = sprt;
  player->etat = 1;
  afficherLutin(sprt, x, y);
}



int cmpt_bas(cellule **pL){
  int i = 0;
  cellule *p = NULL;
  p = *pL;
  while (p != NULL) {
    int a = 0;
    int b = 0;
    tailleLutin(p->lut.sprite, &a, &b);
      if (p->lut.posy == bord_bas(p) - b){
          p->lut.etat = 2;
          i ++;
      }
    p = p->suivant;
  }
  return i;
}



void refresh(cellule *l, cellule *b, cellule *m, lutin p) {
  // Refresh écran
  rectanglePlein(0, 0, LARGEUR, HAUTEUR, 1);

  // Refresh ennemis
  cellule *tmpmstr = NULL;
  tmpmstr = l;

  while (tmpmstr != NULL) {
    afficherLutin(tmpmstr->lut.sprite, tmpmstr->lut.posx, tmpmstr->lut.posy);
    tmpmstr = tmpmstr->suivant;
  }

  // Refresh player
  afficherLutin(p.sprite, p.posx, p.posy);
  
  // Refresh bombes
  cellule *tmpbomb = NULL;
  tmpbomb = b;
  
  while (tmpbomb != NULL){
    afficherLutin(tmpbomb->lut.sprite, tmpbomb->lut.posx, tmpbomb->lut.posy);
    tmpbomb = tmpbomb->suivant;
  }

  // Refresh missiles
  cellule *tmpmssls = NULL;
  tmpmssls = m;

  while (tmpmssls != NULL){
    afficherLutin(tmpmssls->lut.sprite, tmpmssls->lut.posx, tmpmssls->lut.posy);
    tmpmssls = tmpmssls->suivant;
  }
}



int bomber (cellule *l, int cmpt){
    cellule *tmp = NULL;
    tmp = l;
    int x = 0;
    bool cont = 1;
    while ((tmp != NULL) && (cont)){
        if (tmp->lut.etat == 2){
            if (!hasard(0,cmpt)){
                x = tmp->lut.posx;
                cont = 0;
            }
            cmpt --;
        }
        tmp = tmp->suivant;
    }
    return x;
}



void jeu(lutin *p, cellule *l, cellule *b, cellule *m) {
  int go = 1;
  int vitx = 1;
  int tick = 0;
  int shoot = 0;

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

      if (event.key.keysym.sym == SDLK_SPACE) {
        shoot = 1;
      }

      break;
      }

    if (tick % BOMBSPEED == 0) {
        bomb_add(&b, bomber(l, cmpt_bas(&l)), bord_bas(l), bomb);
    }

    if ((tick % MISSILESPEED) && shoot){
      missile_add(&m, p->posx, p->posy, missile, player1);
      shoot = 0;
    }

    usleep(SLEEP);
    refresh(l, b, m, *p);
    vitx = move(&l, &b, &m, vitx);
    SDL_Delay(1);

    tick++;
  }
}



void init(lutin* player, int x, int y, int sprtplr, cellule **pL, int nx, int ny, int e, int sprtmstr, int bord){
    //Initialisation joueur
    init_player(player, x, y, sprtplr);
    
    //Initialisation monstre
    init_list_monster(pL, nx, ny, e, sprtmstr, bord);
}
    


int main(void) {
  initialise_rand();

  creerSurface(LARGEUR, HAUTEUR, "Space Invader");

  cellule *l = NULL;
  cellule *b = NULL;
  cellule *m = NULL;
  lutin p;
  
  player1 = chargerLutin("../Lutins/invader_canon.bmp", 0);
  monster1 = chargerLutin("../Lutins/invader_monstre2_1.bmp", 0);
  // monster2 = chargerLutin("../Lutins/invader_monstre2_2.bmp",0);
  bomb = chargerLutin("../Lutins/invader_bombe.bmp", 0);
  missile = chargerLutin("../Lutins/invader_missile.bmp", 1);

  init(&p, LARGEUR / 2, HAUTEURP, player1, &l, COL, LIN, ECART, monster1, BORD);

  jeu(&p, l, b, m);

  free_list(&l);

  fermerSurface();

  return 0;
}
