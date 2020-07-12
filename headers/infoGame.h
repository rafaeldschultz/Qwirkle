#ifndef _INFOGAME_
#define _INFOGAME_

#include "infoBlock.h"
#include "infoBag.h"

typedef struct{
    //Referentes ao tabuleiro do Jogo
    Block ** board;
    short max_col;
    short max_lin;

    //Referente aos Jogadores
    int n_players;
    
    //Referente a sacola com os 
    Bag bag;
} Game;

#endif
