#include<stdio.h>
#include<stdlib.h>

#include "headers/infoBlock.h"
#include "headers/infoBoard.h"

void createBoard(Board * tafel){
    Block **board = (Block **) malloc(BOARD_DIM * sizeof(Block *));

    for(short i = 0; i < BOARD_DIM; i++){
        board[i] = (Block *) calloc(BOARD_DIM, sizeof(Block)); 
    }

    tafel->tabuleiro = board;

    tafel->max_x = 0;
    tafel->max_y = 0;
}

void eraseBoard(Board * tafel){
    for(short i = 0; i < BOARD_DIM; i++){
        free(tafel->tabuleiro[i]); 
    }
    
    free(tafel->tabuleiro);
}
