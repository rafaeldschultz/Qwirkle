#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "headers/infoBlock.h"
#include "headers/infoGame.h"
#include "headers/players.h"

short ** createBlocksControl(){
    short ** blocksControl = (short **) malloc(6 * sizeof(short *));
    
    for(short i = 0; i < 6; i++){
        blocksControl[i] = (short *) calloc(6, sizeof(short));
    }
    return blocksControl;
}

void deleteBlocksControl(Game *g){
    for(short i = 0; i < 6; i++){
        free(g->blocksControl[i]);
    }
    free(g->blocksControl);
}

short verifyBlock(Game *g, Block b){
    int letter_pos = b.letter - 'A';
    int number_pos = b.number - 1;
    
    if(g->blocksControl[letter_pos][number_pos] < 3){
        g->blocksControl[letter_pos][number_pos]++;
        return 0;
    }

    return 1;
}

short verifyPlayerHand(Player p, Block b){
    for(short i = 0; i < 6; i++){
        if(b.letter == p.tiles[i].letter && b.number == p.tiles[i].number){
            return 1;
        }
    }
    return 0;
}

Block * drawBlocks(Game *g){
    Block * b = (Block *) malloc(HAND_LENGTH * sizeof(Block));
    srand(time(NULL));

    for(short i = 0; i < HAND_LENGTH; i++){
        short error = 1;
        while(error){
            b[i].letter = 'A' + (rand() % 6);
            b[i].number = 1 + (rand() % 6);
            b[i].relation.vertical = 0;
            b[i].relation.horizontal = 0;

            error = verifyBlock(g, b[i]);
        }
    }
    return b;
}

