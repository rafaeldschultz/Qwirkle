#include<stdio.h>
#include<time.h>
#include<stdlib.h>

/*Structs*/
#include "headers/infoGame.h"
#include "headers/infoBlock.h"

#include "headers/board.h"
#include "headers/output.h"
#include "headers/players.h"
#include "headers/blocks.h"
#include "headers/game.h"

int main(int argc, char *argv[]){
    srand(time(0));

    Game g;
    welcome();
    createBoard(&g);
    g.bag = createBag();
    
    Player *p = initializePlayers(&g);
    
    gameRounds(&g, p);
    
    deleteBlocksControl(&g);
    deletePlayers(g, p);
    eraseBoard(&g);

    return 0;
}
