#include <unistd.h>
#include <math.h>
#include <stdio.h>
#include "Graphique/libgraph.h"
#include "ListeChainee/list.h"
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#define HAUTEUR 800
#define LARGEUR 1000
#define COL 10
#define LIN 3
#define BORD 0
#define ECART 70
#define BOMBSPEED 10

void init_player(lutin *player, int x, int y, int sprt){
    player->posx = x;
    player->posy = y;
    player->sprite = sprt;
    player->etat = 1;
    afficherLutin(sprt,x,y);
}

int bord_gauche(cellule *l){
    cellule *tmp;
    tmp = l;
    int min = tmp->lut.posx;
    while (tmp != NULL){
        if (tmp->lut.posx < min) min = tmp->lut.posx;
        tmp = tmp->suivant;
    }
    return min;
}

int bord_droit(cellule *l){
    cellule *tmp;
    tmp = l;
    int max = tmp->lut.posx;
    while (tmp != NULL){
        int a; int b;
        tailleLutin(tmp->lut.sprite,&a,&b);
        if (tmp->lut.posx + a > max) max = tmp->lut.posx + a;
        tmp = tmp->suivant;
    }
    return max;
}

int bord_bas(cellule *l){
    cellule *tmp;
    tmp = l;
    int max = tmp->lut.posy;
    while (tmp != NULL){
        int a; int b;
        tailleLutin(tmp->lut.sprite,&a,&b);
        if (tmp->lut.posy + b > max) max = tmp->lut.posy + b;
        tmp = tmp->suivant;
    }
    return max;
}

void move(cellule **pL, int dx, int dy){
    cellule *p;
    p = *pL;
    while(p != NULL){
        p->lut.posx += dx;
        p->lut.posy += dy;
        p = p->suivant;
    }
    majSurface();
}

void refresh(cellule * l, lutin p){
    //Refresh écran
    
    rectanglePlein(0, 0, LARGEUR, HAUTEUR,1);
    
    //Refresh ennemis
    cellule *tmp;
    tmp = l;
    
    while(tmp != NULL){
        afficherLutin(tmp->lut.sprite,tmp->lut.posx,tmp->lut.posy);
        tmp = tmp->suivant;
    }
    
    //Refresh player
    
    afficherLutin(p.sprite, p.posx, p.posy);
}
    
    
int move_line(cellule **pL, int vitx){
    if (bord_gauche(*pL) >= BORD && bord_droit(*pL) <= LARGEUR-BORD){
        if (vitx == 1) move(pL, 5, 0);
        else move(pL, -5, 0);
    }
        
    else if (bord_gauche(*pL) < BORD){
        vitx = 1;
        move(pL, 5, 15);
    }
        
    else if (bord_droit(*pL) > LARGEUR-BORD){
        vitx = -1;
        move(pL, -5, 15);
    }
    return vitx;
}

void jeu(lutin *p, cellule *l){
    int go = 1;
    int vitx = 1;
    int tick = 0;
    
    int taille[2];
    tailleLutin(p->sprite, &taille[0], &taille[1]);
    
    while(go){
        
        SDL_Event event;
        SDL_PollEvent(&event);
        
        switch (event.type){
        case SDL_QUIT:
            go = 0;
            break;
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_RIGHT){
                if (p->posx < LARGEUR - BORD - taille[0]) p->posx += 5 ;
                printf("%d\n", p->posx);
            }
            
            if (event.key.keysym.sym == SDLK_LEFT){
                if (p->posx > BORD) p->posx -= 5;
                printf("%d\n", p->posx);
            }
            
            break;
        }
        
        if (tick % BOMBSPEED == 0){
            
        }
        
        usleep(10000);
        refresh(l, *p);
        vitx = move_line(&l,vitx);
        SDL_Delay(1);
        
        tick ++;
    }
}
        
        
int main(void){
    creerSurface(LARGEUR,HAUTEUR,"Bonjour");
    
    int player1 = chargerLutin("../Lutins/invader_canon.bmp",5);
    int monster1 = chargerLutin("../Lutins/invader_monstre2_1.bmp",5);
    //int monster2 = chargerLutin("../Lutins/invader_monstre2_2.bmp",5);
    int bomb = chargerLutin("../Lutins/invader_bombe.bmp",5);
    
//     int taille1[2];
//     
//     tailleLutin(monster1, &taille1[0], &taille1[1]);
    
    cellule *l = NULL;
    
    lutin p;
    init_player(&p, LARGEUR/2, HAUTEUR-50,player1);
    
    init_list_monster(&l, COL, LIN, ECART, monster1, BORD);
    
    cellule *b = NULL;
    
    jeu(&p, l);
    
//     int rangex = LARGEUR - (2*BORD + taille1[0] + (COL-1)*ECART);
    //int rangey = HAUTEUR - (2*BORD + taille1[1] + (LIN-1)*ECART);
    
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
//             move(&l, 1, 0);
//         }
//         
//         for(int j = 0; j<rangex; j++){
//             move(&l, -1, 0);
//         }
    
    free_list(&l);
    
    fermerSurface();
    
    return 0;
}
