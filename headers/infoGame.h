#ifndef _INFOGAME_
#define _INFOGAME_

#include "infoBlock.h"
#include "infoBag.h"

typedef struct{
    Block ** board;
    short max_col;
    short max_lin;
    int n_players;
    Bag bag;
} Game;

#endif
