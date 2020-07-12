#include<stdio.h>
#include<stdlib.h>

/* Arquivos contendo structs*/
#include "headers/infoBlock.h"
#include "headers/infoGame.h"

#include "headers/output.h"

/*
 * Aloca o tabuleiro na heap
 * Atribui esse tabuleiro, com as casas todas vazias, a Struct Game
 */
void createBoard(Game *g){
    Block **b = (Block **) malloc(sizeof(Block *));     //Aloca um ponteiro para ponteiros na heap
    if(b == NULL) {                     //verifica se foi alocado com sucesso
        errorAllocation();
        exit(1);
    }
    /*
     * Como aloca cada um dos ponteiros na heap. 
     * Como o tabuleiro começa com apenas um espaco, aloca apenas um ponteiro do tipo Block 
     */    
    b[0] = (Block *) calloc(1, sizeof(Block));      
    if(b[0] == NULL) {                  //verifica se foi alocado com sucesso
        errorAllocation();
        exit(1);
    }

    g->board = b;                       //Atribui o tabuleiro criado ao tabuleiro presente em g

    g->max_lin = 0;                     //Como ha apenas uma linha, atribui 0 a max_lin de g
    g->max_col = 0;                     //Como ha apenas uma coluna, atribui 0 a max_col de g
}

/*
 * Libera a memoria ocupada pelo tabuleiro na heap
 */
void eraseBoard(Game * g){
    for(short i = 0; i < g->max_col; i++){
        free(g->board[i]);                  //libera as colunas
    }
    
    free(g->board);                         //libera as linhas
}
