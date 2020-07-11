#include<stdio.h>

/*Structs*/
#include "headers/infoGame.h"
#include "headers/infoBlock.h"

#include "headers/board.h"
#include "headers/output.h"
#include "headers/players.h"
#include "headers/blocks.h"

int main(int argc, char *argv[]){
    Game g;
    
    welcome();
    createBoard(&g);
    g.blocksControl = createBlocksControl();
    
    Player *p = initializePlayers(&g);
    
    showBoard(&g);
    showPlayersTiles(g, p);
    
    deleteBlocksControl(&g);
    deletePlayers(g, p);
    eraseBoard(&g);

    return 0;
}
