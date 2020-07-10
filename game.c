#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "headers/infoGame.h"
#include "headers/infoPlayer.h"

#include "headers/colors.h"
#include "headers/buffer.h"

Block * drawBlocks(){
    Block * b = (Block *) malloc(HAND_LENGTH * sizeof(Block));
    srand(time(0));

    for(short i = 0; i < HAND_LENGTH; i++){
        b[i].letter = 'A' + (rand() % 6);
        b[i].number = 1 + (rand() % 6); 
    }
    return b;
}

void deletePlayers(Game g, Player *p){
    for(int i = 0; i < (g.n_players); i++){
        free(p[i].tiles);
    }

    free(p);
}

Player * initializePlayers(Game *g){
    green(1);
    printf("Numero de jogadores: ");
    reset();

    scanf("%d", &g->n_players);

    Player * p = (Player *) malloc((g->n_players) * sizeof(Player));
    
    cleanBufferEnter();
    for(int i = 0; i < (g->n_players); i++){
        green(1);
        printf("Nome do Jogador ");
        blue(1);
        printf("#%d: ", i);
        reset();
        fgets(p[i].name, NAME_LENGTH, stdin);

        char *espaco = strchr(p[i].name, '\n');
        *espaco = '\0';
        
        p[i].tiles = drawBlocks();
    }

    return p;
}
