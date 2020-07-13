#include <stdio.h>

#include "headers/infoGame.h"
#include "headers/infoMove.h"
#include "headers/infoBlock.h"
#include "headers/infoPlayer.h"
#include "headers/output.h"

/*
 * Define a pontuacao acima da peca firstMove
 */
int defineScoreUp(Game *g, Move firstMove){
    short i = 1;

    /*
     * Conta quantas pecas acima da firstmove
     */
    while(firstMove.lin - i > 0){
        if(g->board[firstMove.lin - i][firstMove.col].letter == '\0'){
            break;
        }
        i++;
    }

    return i;   //retorna a quantidade de pecas acima de firstMove, incluindo a propria peca
}

/*
 * Define a pontuacao abaixo da peca firstMove
 */
int defineScoreDown(Game *g, Move firstMove){    
    short i = 1;

    /*
     * Conta quantas pecas abaixo da firstmove
     */
    while(firstMove.lin + i < g->max_lin){
        if(g->board[firstMove.lin + i][firstMove.col].letter == '\0'){
            break;
        }
        i++;
    }

    return i;   //retorna a quantidade de pecas abaixo de firstMove, incluindo a propria peca
}

/*
 * Define a pontuacao a esquerda da peca firstMove
 */
int defineScoreLeft(Game *g, Move firstMove){
    short i = 1;

    /*
     * Conta quantas a esquerda abaixo da firstmove
     */
    while(firstMove.col - i > 0){
        if(g->board[firstMove.lin][firstMove.col - i].letter == '\0'){
            break;
        }
        i++;
    }

    return i;   //retorna a quantidade de pecas a esquerda de firstMove, incluindo a propria peca
}

/*
 * Define a pontuacao a direita da peca firstMove
 */
int defineScoreRight(Game *g, Move firstMove){
    Block first = g->board[firstMove.lin][firstMove.col];
    
    short i = 1;

    /*
     * Conta quantas a direita abaixo da firstmove
     */
    while(firstMove.col + i < g->max_col){
        if(g->board[firstMove.lin][firstMove.col + i].letter == '\0'){
            break;
        }
        i++;
    }

    return i;   //retorna a quantidade de pecas a direita de firstMove, incluindo a propria peca
}

/*
 * Define o score de uma peca nas quatro direcoes
 */
int defineScoreFirstMove(Game *g, Move firstMove){
    int score = 0, score1 = -1;
    
    score1 += defineScoreUp(g, firstMove);      //Calcula o score acima de first move
    score1 += defineScoreDown(g, firstMove);    //Calcula o score abaixo de first move
    
    if(score1 == 6){
        score1 += 6;                            //Fez um Qwirkle
    }
    
    score += score1;                            //Calcula o score total
    score1 = -1;

    score1 += defineScoreLeft(g, firstMove);    //Calcula o score a esquerda de first move
    score1 += defineScoreRight(g, firstMove);   //Calcula o score a direita de first move

    if(score1 == 6){
        score1 += 6;                            //Fez um Qwirkle
    }
    
    score += score1;                            //Calcula o score total

    return score;
}

/*
 * Define o jogador vencedor da partida
 */
void winner(Game *g, Player *players){
    int i;
    int highScore = 0;
    int userHighScore = 0;

    for(i = 0; i < g->n_players; i++){
        if(players[i].score > highScore){
            highScore = players[i].score;   //Verifica a maior pontuacao
            userHighScore = i;              //Verifica o usuario com maior pontuacao
        }
    }
    showWinner(players[userHighScore]);
}
