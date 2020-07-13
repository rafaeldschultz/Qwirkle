#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "headers/infoBlock.h"
#include "headers/infoGame.h"
#include "headers/infoBag.h"

#include "headers/output.h"
#include "headers/players.h"
#include "headers/board.h"


/******************
 * BAG WITH TILES *
 ******************/

/*
 * Aloca na heap o controle da quantidade de blocos de cada tipo no jogo
 * Linhas da matriz indicam a letra e colunas o numero do bloco
 * Podem existir no maximo 3 blocos iguais
 */
void createBag(Game *g){
    g->bag.blocksControl = (short **) malloc(6 * sizeof(short *));  //aloca um ponteiro de ponteiros do tipo short e tam = 6 na heap
    if(g->bag.blocksControl == NULL){                               //verifica se foi alocado com sucesso
        errorAllocation();
        eraseBoard(g);                                              //Desaloca o que ja havia sido alocado
        exit(1);
    }

    for(short i = 0; i < 6; i++){
        g->bag.blocksControl[i] = (short *) calloc(6, sizeof(short));   //aloca e inicializa todas as posicoes da matriz de controle com valores nulos
        
        if(g->bag.blocksControl == NULL){
            errorAllocation();
            free(g->bag.blocksControl);
            eraseBoard(g);                                          //Desaloca o que ja havia sido alocado
            exit(1);
        }
    }

    g->bag.blocks_number = BLOCKS_TOTAL_NUMBER;                     //Atribui a quantidade de blocos disponiveis o total no jogo (padrao = 108 pecas)
}

/*
 * Libera da memoria o controle de blocos distribuidos
 */
void deleteBlocksControl(Game *g){
    for(short i = 0; i < 6; i++){      
        free(g->bag.blocksControl[i]);  //libera as colunas
    }
    free(g->bag.blocksControl);         //libera as linhas
}

/*
 * Incrementa a quantidade de blocos na sacola
 */
void incrementBag(Game *g){
    g->bag.blocks_number++;
}

/*
 * Decrementa o numero de blocos na sacola
 */
void decrementBag(Game *g){
    g->bag.blocks_number--;
}


/****************
 * VERIFICACOES *
 ****************/

/*
 * Verifica se o bloco esta disponivel para ser sorteado
 * Utilizado pelas funcoes de sorteio de blocos
 */
short verifyBlock(Game *g, Block b){
    int letter_pos = b.letter - 'A';                        //Descobre a posicao na matriz da letra (linha)
    int number_pos = b.number - 1;                          //Descobre a posicao na matriz da letra (coluna)
    
    if(g->bag.blocksControl[letter_pos][number_pos] < 3){   //Verifica se a quantidade de pecas iguais a b no jogo eh menor que 3
        g->bag.blocksControl[letter_pos][number_pos]++;     //Se sim, soma um a quantidade de pecas
        return 0;
    }

    return 1;
}

/* 
 * Verifica se uma peca existe na mao de um jogador
 */
short verifyPlayerHand(Player p, Block b){
    for(short i = 0; i < 6; i++){                                               //Verifica todas as pecas
        if(b.letter == p.tiles[i].letter && b.number == p.tiles[i].number){
            return 1;                                                           //Se encontrar a peca, retorna 1
        }
    }
    return 0;
}


/***********
 * SORTEIO *
 ***********/

/*
 * Sorteia apenas uma peca
 * Utilizado na funcao 'trocar' do jogo
 */
Block drawOneBlock(Game *g){
    Block b;

    short error = 1;
    while(error){                                       //Sorteia ate o bloco ser valido
        b.letter = 'A' + (rand() % 6);                  //Sorteia uma letra entre 'A' e 'F'
        b.number = 1 + (rand() % 6);                    //Sorteia um numero entre 1 e 6
        b.relation.vertical = 0;                        //Atribui 0 (indefinido) a relacao vertical, ja que nao esta no tabulerio
        b.relation.horizontal = 0;                      //Atribui 0 (indefinido) a relacao horizontal, ja que nao esta no tabulerio

        error = verifyBlock(g, b);                      //verifica se o bloco pode ser sorteado
    }

    decrementBag(g);                                    //Diminui um bloco da sacola
    return b;
}

/*
 * Sorteia toda a mao de um jogador (padrao = 6 blocos)
 */
Block * drawBlocks(Game *g){
    Block * b = (Block *) malloc(HAND_LENGTH * sizeof(Block));      //Aloca um vetor para armazenar as pecas do jogador
    if(b == NULL){                                                  //Verifica por erros de alocacao
        errorAllocation();
        exit(0);
    }

    for(short i = 0; i < HAND_LENGTH; i++){             
        b[i] = drawOneBlock(g);                                     //sorteia um bloco
    }
    return b;
}

/*
 * Completa a mao do jogador a quantidade de pecas necessaria
 */
void completeBlocksNumber(Game *g, Player *p){
    for(short i = 0; i < 6; i++){
        if(p->tiles[i].letter == '\0'){     //verifica se o bloco de posicao i na mao do jogador eh vazio
            p->tiles[i] = drawOneBlock(g);  //Se sim, sorteia uma peca
        }
    }
}


/********************************
 * ALTERAR BLOCOS DE UM JOGADOR *
 ********************************/

/*
 * Remove um bloco da mao de um jogador 
 */
void removeBlockFromHand(Player *p, Block b){
    for(short i = 0; i < 6; i++){
        if(p->tiles[i].letter == b.letter && p->tiles[i].number == b.number){       //Verifica se o bloco eh o procurado na mao do jogador
            p->tiles[i].letter = '\0';                                              //Se sim, atribui vazio as suas propriedades
            p->tiles[i].number = 0;
            p->tiles[i].relation.horizontal = 0;
            p->tiles[i].relation.vertical = 0;
            break;
        }   
    }
}

/*
 * Troca um bloco por outro de um jogador 
 */
void changeBlock(Game *g, Player *p, Block b){
    removeBlockFromHand(p, b);                                  //Remove o bloco da mao do usuario

    //Encontra a posicao de seus termos na matriz de controle
    short letter_pos = b.letter - 'A';                  
    short number_pos = b.number - 1;

    (g->bag.blocksControl[letter_pos][number_pos])--;           //Subtrai um da quantidade disponivel no jogo (ja que a peca volta para o saco)
    (g->bag.blocks_number)++;                                   //Adiciona uma peca a quantidade disponivel na sacola

    completeBlocksNumber(g, p);                                 //Sorteia um novo bloco
}
