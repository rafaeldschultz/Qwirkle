#include "infoBlock.h"

#ifndef _INFOPLAYER_
#define _INFOPLAYER_

#define NAME_LENGTH 15

typedef struct{
    char name[NAME_LENGTH];
    Block *tiles; 
} Player;

#endif
