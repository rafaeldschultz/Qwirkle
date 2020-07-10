#include<stdio.h>
#include<stdlib.h>

#include "headers/infoBlock.h"
#include "headers/infoGame.h"

void createBoard(Game *g){
    Block **b = (Block **) malloc(sizeof(Block *));

    for(short i = 0; i < 1; i++){
        b[i] = (Block *) calloc(1, sizeof(Block)); 
    }

    g->board = b;

    g->max_lin = 0;
    g->max_col = 0;
}

void eraseBoard(Game * g){
    for(short i = 0; i < g->max_col; i++){
        free(g->board[i]); 
    }
    
    free(g->board);
}
