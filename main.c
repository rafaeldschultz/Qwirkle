#include<stdio.h>

/*Structs*/
#include "headers/infoGame.h"
#include "headers/infoBlock.h"

#include "headers/board.h"
#include "headers/output.h"
#include "headers/game.h"

int main(int argc, char *argv[]){
    //tafel = tabuleiro em alemao
    Game g;
    
    welcome();
    createBoard(&g);
    Player *p = initializePlayers(&g);

    showBoard(&g);
    showPlayersTiles(g, p);
    
    deletePlayers(g, p);
    eraseBoard(&g);
    return 0;
}
