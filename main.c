#include<stdio.h>

#include "headers/infoBoard.h"
#include "headers/board.h"
#include "headers/output.h"

#include "headers/infoBlock.h"

int main(int argc, char *argv[]){
    //tafel = tabuleiro em alemao
    Board tafel;
    
    createBoard(&tafel);

    showBoard(&tafel);

    eraseBoard(&tafel);

    return 0;
}
