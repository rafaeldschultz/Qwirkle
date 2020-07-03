#ifndef _INFOBOARD_
#define _INFOBOARD_

#include "infoBlock.h"

#define BOARD_DIM 92

typedef struct{
    Block ** tabuleiro;
    short max_x;
    short max_y;
} Board;

#endif
