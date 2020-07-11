#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "headers/infoBlock.h"
#include "headers/infoGame.h"

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

Block * drawBlocks(Game *g){
    Block * b = (Block *) malloc(HAND_LENGTH * sizeof(Block));
    srand(time(0));

    for(short i = 0; i < HAND_LENGTH; i++){
        short error = 1;
        while(error){
            b[i].letter = 'A' + (rand() % 6);
            b[i].number = 1 + (rand() % 6);
            
            error = verifyBlock(g, b[i]);
        }
    }
    return b;
}
