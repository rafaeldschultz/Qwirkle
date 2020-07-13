#include <stdio.h>

#include "headers/infoGame.h"
#include "headers/infoMove.h"
#include "headers/infoBlock.h"

int defineScoreUp(Game *g, Move firstMove){
    Block first = g->board[firstMove.lin][firstMove.col];
    
    short i = 1;

    while(firstMove.lin - i > 0){
        if(g->board[firstMove.lin - i][firstMove.col].letter == '\0'){
            break;
        }
        i++;
    }

    return i;
}

int defineScoreDown(Game *g, Move firstMove){
    Block first = g->board[firstMove.lin][firstMove.col];
    
    short i = 1;

    while(firstMove.lin + i < g->max_lin){
        if(g->board[firstMove.lin + i][firstMove.col].letter == '\0'){
            break;
        }
        i++;
    }

    return i;
}

int defineScoreLeft(Game *g, Move firstMove){
    Block first = g->board[firstMove.lin][firstMove.col];
    
    short i = 1;

    while(firstMove.col - i > 0){
        if(g->board[firstMove.lin][firstMove.col - i].letter == '\0'){
            break;
        }
        i++;
    }

    return i;
}

int defineScoreRight(Game *g, Move firstMove){
    Block first = g->board[firstMove.lin][firstMove.col];
    
    short i = 1;

    while(firstMove.col + i < g->max_col){
        if(g->board[firstMove.lin][firstMove.col + i].letter == '\0'){
            break;
        }
        i++;
    }

    return i;
}


int defineScoreFirstMove(Game *g, Move firstMove){
    int score = -2;
    score += defineScoreUp(g, firstMove);
    score += defineScoreDown(g, firstMove);
    score += defineScoreLeft(g, firstMove);
    score += defineScoreRight(g, firstMove);

    return score;
}
