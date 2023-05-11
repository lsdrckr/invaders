# Space Invaders

Vous êtes face à la version de Space Invaders de Louis DERYCKERE. Je vais vous apprendre ici comment l'utiliser et le paramétrer à votre guise !

## Paramétrages

Vous pouvez réaliser différents paramétrages selon vos désirs comme les suivants :

### Fenêtre de jeu


Ce paramètre peut être modifié en changeant les valeurs suivantes par celles souhaitées :

```c
#define HAUTEUR xxxx
#define LARGEUR xxxx
```

ATTENTION : Ces valeurs sont à modifier à la fois dans `main.c` et dans `move.c` !

### Position des ennemis

Les différentes valeurs liés à la position des ennemis peuvent être modifiés comme suit :

```c
#define BORD xxxx
#define COL xxxx
#define LIN xxxx
#define ECART xxxx
```

ATTENTION : Ces valeurs sont à modifier à la fois dans `main.c` et dans `move.c` !

### Difficulté du jeu

Enfin, vous pouvez modifier également la difficultés du jeu en modifiant :

```c
#define VITXM xxxx
#define VITYM xxxx
#define VITYB xxxx
#define VITYMISS xxxx
#define BOMBSPEED xxxx
#define MISSILESPEED xxxx
#define VITXP xxxx
```

ATTENTION : Ces valeurs sont à modifier à la fois dans `main.c` et dans `move.c` !

##Contrôles

Le vaisseau joueur peut être contrôler de gauche à droite avec les touches `ARROW_LEFT` et `ARROW_RIGHT`. Vous pouvez également tirer en touchant `SPACE`.

##Lancement de la partie

Rendez vous dans le repertoire src en tapant `cd ProjetInvaders/src` dans le terminal. C'est depuis ce repértoire que vous pourrez lancer la partie et jouer au jeu. Pour lancer une partie, taper les deux commandes suivantes :

```bash
make
./main
```

et profiter de votre jeu !

Vous pouvez également formater les fichier au format Webkit en tapant `make format`, et vérifier que le code est propre avec `make tidy`. Enfin, vous pouvez supprimer les executables en tapant `make clean`. 

##BON AMUSEMENT !
