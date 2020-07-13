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
    int score = 0, score1 = -1;
    
    score1 += defineScoreUp(g, firstMove);
    score1 += defineScoreDown(g, firstMove);
    
    if(score1 == 6){
        score1 += 6;                        //Fez um Qwirkle
    }
    
    score += score1;
    score1 = -1;
    
    score1 += defineScoreLeft(g, firstMove);
    score1 += defineScoreRight(g, firstMove);

    if(score1 == 6){
        score1 += 6;                        //Fez um Qwirkle
    }
    
    score += score1;

    return score;
}
