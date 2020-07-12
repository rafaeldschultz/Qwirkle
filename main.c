#include <stdio.h>
#include <time.h>
#include <stdlib.h>

/*Arquivos com Structs*/
#include "headers/infoGame.h"
#include "headers/infoBlock.h"

#include "headers/output.h"
#include "headers/game.h"

int main(int argc, char *argv[]){
    srand(time(0));             //Determina a semente para a função rand() como o tempo atual
    welcome();                  //Imprime mensagens de Boas-Vindas

    Game g;                     
    Player *p = NULL;
    createGame(&g, &p);         //Cria os membros do jogo
    
    gameRounds(&g, p);          //Inicia as rodadas do jogo
    
    deleteGame(&g, &p);         //Deleta o jogo

    return 0;
}
