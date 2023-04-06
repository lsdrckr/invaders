#include "Graphique/libgraph.h"
#include "ListeChainee/list.h"
#include "Random/alea.h"
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <math.h>
#include <stdio.h>
#include <unistd.h>

#define HAUTEUR 800
#define LARGEUR 1000
#define COL 10
#define LIN 3
#define BORD 0
#define ECART 70
#define BOMBSPEED 10
#define VITXM 5
#define VITYM 15
#define VITYB -5
#define VITXP 5
#define SLEEP 10000
#define HAUTEURP (HAUTEUR - 50)



//Variables globales
int player1;
int monster1;
// int monster2;
int bomb;



void init_player(lutin *player, int x, int y, int sprt) {
  player->posx = x;
  player->posy = y;
  player->sprite = sprt;
  player->etat = 1;
  afficherLutin(sprt, x, y);
}



int bord_gauche(cellule *l) {
  cellule *tmp = NULL;
  tmp = l;
  int min = LARGEUR;
  while (tmp != NULL) {
    if (tmp->lut.posx < min) {
      min = tmp->lut.posx;
    }
    tmp = tmp->suivant;
  }
  return min;
}



int bord_droit(cellule *l) {
  cellule *tmp = NULL;
  tmp = l;
  int max = 0;
  while (tmp != NULL) {
    int a = 0;
    int b = 0;
    tailleLutin(tmp->lut.sprite, &a, &b);
    if (tmp->lut.posx + a > max) {
      max = tmp->lut.posx + a;
    }
    tmp = tmp->suivant;
  }
  return max;
}



int bord_bas(cellule *l) {
  cellule *tmp = NULL;
  tmp = l;
  int max = tmp->lut.posy;
  while (tmp != NULL) {
    int a = 0;
    int b = 0;
    tailleLutin(tmp->lut.sprite, &a, &b);
    if (tmp->lut.posy + b > max) {
      max = tmp->lut.posy + b;
    }
    tmp = tmp->suivant;
  }
  return max;
}



void move_mstr(cellule **pL, int dx, int dy) {
  cellule *p = NULL;
  p = *pL;
  while (p != NULL) {
    p->lut.posx += dx;
    p->lut.posy += dy;
    p = p->suivant;
  }
  majSurface();
}




void move_bomb(cellule **pL, int dy) {
  cellule *p = NULL;
  p = *pL;
  while (p != NULL) {
    p->lut.posy += dy;
    p = p->suivant;
  }
  majSurface();
}


int is_bomber(cellule **pL){
  int cmpt = 0;
  cellule *p = NULL;
  p = *pL;
  while (p != NULL) {
      if (p->lut.posy == bord_bas(p)){
          p->lut.etat = 2;
          cmpt ++;
      }
    p = p->suivant;
  }
  return cmpt;
}



void refresh(cellule *l, lutin p) {
  // Refresh écran

  rectanglePlein(0, 0, LARGEUR, HAUTEUR, 1);

  // Refresh ennemis
  cellule *tmp = NULL;
  tmp = l;

  while (tmp != NULL) {
    afficherLutin(tmp->lut.sprite, tmp->lut.posx, tmp->lut.posy);
    tmp = tmp->suivant;
  }

  // Refresh player

  afficherLutin(p.sprite, p.posx, p.posy);
}



int move(cellule **pL, cellule **pB, int vitx) {
  if (bord_gauche(*pL) >= BORD && bord_droit(*pL) <= LARGEUR - BORD) {
    if (vitx == 1) {
      move_mstr(pL, VITXM, 0);
    } else {
      move_mstr(pL, -1 * VITXM, 0);
    }
  }

  else if (bord_gauche(*pL) < BORD) {
    vitx = 1;
    move_mstr(pL, VITXM, VITYM);
  }

  else if (bord_droit(*pL) > LARGEUR - BORD) {
    vitx = -1;
    move_mstr(pL, -1 * VITXM, VITYM);
  }
  
  move_bomb(pB, VITYB);
  
  return vitx;
}



void jeu(lutin *p, cellule *l, cellule *b) {
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

      break;
    }

    if (tick % BOMBSPEED == 0) {
        
        bomb_add(&b, 0, bord_bas(l), bomb);
    }

    usleep(SLEEP);
    refresh(l, *p);
    vitx = move(&l, &b, vitx);
    SDL_Delay(1);

    tick++;
  }
}



void init(lutin* player, int x, int y, int sprtplr, cellule **pL, int nx, int ny, int e, int sprtmstr, int bord){
    //Initialisation joueur
    init_player(player, x, y, sprtplr);
    
    //Initialisation monstre
    init_list_monster(pL, nx, ny, e, sprtmstr, bord);
    
    player1 = chargerLutin("../Lutins/invader_canon.bmp", 0);
    monster1 = chargerLutin("../Lutins/invader_monstre2_1.bmp", 0);
    // monster2 = chargerLutin("../Lutins/invader_monstre2_2.bmp",0);
    bomb = chargerLutin("../Lutins/invader_bombe.bmp", 0);
}
    


int main(void) {
  initialise_rand();

  creerSurface(LARGEUR, HAUTEUR, "Bonjour");

  int player1 = chargerLutin("../Lutins/invader_canon.bmp", 0);
  int monster1 = chargerLutin("../Lutins/invader_monstre2_1.bmp", 0);
  // int monster2 = chargerLutin("../Lutins/invader_monstre2_2.bmp",0);
  // int bomb = chargerLutin("../Lutins/invader_bombe.bmp", 0);

  //     int taille1[2];
  //
  //     tailleLutin(monster1, &taille1[0], &taille1[1]);

  cellule *l = NULL;
  cellule *b = NULL;
  lutin p;
  
  init(&p, LARGEUR / 2, HAUTEURP, player1, &l, COL, LIN, ECART, monster1, BORD);

  jeu(&p, l, b);

  //     int rangex = LARGEUR - (2*BORD + taille1[0] + (COL-1)*ECART);
  // int rangey = HAUTEUR - (2*BORD + taille1[1] + (LIN-1)*ECART);

  //     int compt_sprt = 0;

  //         if (compt_sprt == 50){
  //             for (int i = 0; i < COL*LIN; i++){
  //                 l->lut.sprite = monster2;
  //                 l = l->suivant;
  //             }
  //             compt_sprt = 0;
  //         }
  //
  //         else if (compt_sprt == 25){
  //             for (int i = 0; i < COL*LIN; i++){
  //                 l->lut.sprite = monster1;
  //                 l = l->suivant;
  //             }
  //         }
  //
  //         compt_sprt++;
  //
  //         for(int i = 0; i<rangex; i++){
  //             move_mstr(&l, 1, 0);
  //         }
  //
  //         for(int j = 0; j<rangex; j++){
  //             move_mstr(&l, -1, 0);
  //         }

  free_list(&l);

  fermerSurface();

  return 0;
}
