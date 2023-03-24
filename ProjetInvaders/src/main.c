#include <unistd.h>
#include <math.h>
#include <stdio.h>
#include "Graphique/libgraph.h"
#include "ListeChainee/list.h"
#define HAUTEUR 600
#define LARGEUR 1500
#define COL 12
#define LIN 4
#define BORD 1
#define ECART 70

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
        if (tmp->lut.posx > max) max = tmp->lut.posx;
        tmp = tmp->suivant;
    }
    return max;
}

void move(cellule **pl, int dx, int dy){
    rectanglePlein(0,0,LARGEUR,HAUTEUR-100,1);
    cellule *p;
    p = *pl;
    while(p != NULL){
        p->lut.posx += dx;
        p->lut.posy += dy;
        afficherLutin(p->lut.sprite,p->lut.posx,p->lut.posy);
        p = p->suivant;
    }
    majSurface();
}

void move_line(cellule **pl, int vitx){
    if (bord_gauche(*pl) >= BORD && bord_droit(*pl) >= LARGEUR-BORD){
        if (vitx == 1) move(pl, 5, 0);
        else move(pl, -5, 0);
    }
        
    else if (bord_gauche(*pl) < BORD){
        vitx = 1;
        move(pl, 5, 5);
    }
        
    else if (bord_droit(*pl) > LARGEUR-BORD){
        vitx = -1;
        move(pl, -5, 5);
    }
    printf("%d\n", bord_droit(*pl));
}

int main(void){
    creerSurface(LARGEUR,HAUTEUR,"Bonjour");
    
    int player1 = chargerLutin("../Lutins/invader_canon.bmp",5);
    int monster1 = chargerLutin("../Lutins/invader_monstre2_1.bmp",5);
    //int monster2 = chargerLutin("../Lutins/invader_monstre2_2.bmp",5);
    int taille1[2];
    
    tailleLutin(monster1, &taille1[0], &taille1[1]);
    
    cellule *l = NULL;
    
    lutin p;
    init_player(&p, LARGEUR/2, HAUTEUR-50,player1);
    
    init_liste(&l, COL, LIN, ECART, monster1, BORD);
    
    //int rangex = LARGEUR - (2*BORD + taille1[0] + (COL-1)*ECART);
    //int rangey = HAUTEUR - (2*BORD + taille1[1] + (LIN-1)*ECART);
    
    int game = 1;
    int vitx = 1;
    /*evenement *evt;
    char *touche;
    int compt_sprt = 0;*/
    
    while(game){
        
        usleep(10000);
        
        //lireEvenement(evt, touche, NULL);
        
        //move(&l,5,0);
        
        move_line(&l,1);
        
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
            
//         for(int i = 0; i<rangex; i++){
//             move(&l, 1, 0);
//         }
//         
//         for(int j = 0; j<rangex; j++){
//             move(&l, -1, 0);
//         }
    }
    
    print_list(l);
    
    free_list(&l);
    
    fermerSurface();
    
    return 0;
}
