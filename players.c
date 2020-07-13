#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

/*Arquivos contendo Structs*/
#include "headers/infoGame.h"
#include "headers/infoPlayer.h"

#include "headers/colors.h"
#include "headers/buffer.h"
#include "headers/output.h"
#include "headers/blocks.h"
#include "headers/board.h"

/*
 * Inicializa todos os jogadores
 */
void initializePlayers(Game *g, Player **players){
    green(1);
    printf("Numero de jogadores: ");
    reset();

    char n_player_c = fgetc(stdin);                     //Recebe o numero de jogadores
    cleanBufferEnter();                                 //Limpa o buffer de entrada ate o enter
    
    if(n_player_c >= '1' && n_player_c <= '4'){
        g->n_players = (short) atoi(&n_player_c);       //Se o valor for valido, armazena na struct Game
        
        Player * p = (Player *) malloc((g->n_players) * sizeof(Player));    //Aloca na heap espaco para armenar as informacoes dos jogadores
        
        /*
         * Verifica por erros de alocacao.
         * Se erros, desaloca o que ja foi alocado e finaliza o programa.
         */
        if(p == NULL) {                                 
            errorAllocation();
            deleteBlocksControl(g);
            eraseBoard(g);
            exit(1);
        }

        for(int i = 0; i < (g->n_players); i++){        //Recebe as informacoes dos jogadores
            green(1);
            printf("Nome do Jogador ");
            blue(1);
            printf("#%d: ", i + 1);
            reset();
            fgets(p[i].name, NAME_LENGTH, stdin);       //Recebe o nome do jogador

            char *enter = strchr(p[i].name, '\n');      //retira o enter ao final do nome dos jogadores
            if(enter != NULL) *enter = '\0';            //Se encontrar enter, elimina-o da string
            
            p[i].tiles = drawBlocks(g);                 //sorteia blocos para os jogadores
            p[i].score = 0;                             //atribui 0 ao score inicial
        }

        *players = p;                                   //Atribui o ponteiro com os usuarios ao ponteiro players
    } else {
        invalidNumberPlayers();
    }         
}

/*
 * Libera a memória utilizada para armazenas os usuarios
 * Executada ao final do programa
 */
void deletePlayers(Game g, Player *p){
    for(int i = 0; i < (g.n_players); i++){
        free(p[i].tiles);                   //Libera cada a lista de blocos dos jogadores
    }

    free(p);                                //Libera os jogadores
}
