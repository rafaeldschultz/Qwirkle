#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "headers/infoBlock.h"
#include "headers/infoGame.h"
#include "headers/infoPlayer.h"

#include "headers/colors.h"
#include "headers/output.h"
#include "headers/buffer.h"
#include "headers/blocks.h"

int makeMoviment(Game *g, Block b, int lin, int col){
    g->board[lin][col] = b;

    Block empty;
    empty.letter = '\0';
    empty.number = 0;
    empty.relation.horizontal = 0;
    empty.relation.vertical = 0;

    if(lin == g->max_lin){
        g->max_lin++;
        g->board = (Block **) realloc(g->board, (g->max_lin + 1) * sizeof(Block *));
        g->board[g->max_lin] = (Block *) calloc(g->max_col + 1, sizeof(Block));
    }

    if(lin == 0){
        g->max_lin++;
        g->board = (Block **) realloc(g->board, (g->max_lin + 1) * sizeof(Block *));
        g->board[g->max_lin] = (Block *) calloc(g->max_col + 1, sizeof(Block));

        Block *temp = g->board[g->max_lin];

        for(short i = g->max_lin; i > 0; i--){
            g->board[i] = g->board[i - 1];
        }

        g->board[0] = temp; 
    }

    if(col == g->max_col){
        g->max_col++;
        
        for(short i = 0; i < g->max_lin + 1; i++){
            g->board[i] = (Block *) realloc(g->board[i], (g->max_col + 1) * sizeof(Block));
            g->board[i][g->max_col] = empty;
        }
    }

    if(col == 0){
        g->max_col++;
        
        for(short i = 0; i < g->max_lin + 1; i++){
            g->board[i] = (Block *) realloc(g->board[i], (g->max_col + 1) * sizeof(Block));
            for(short j = g->max_col; j > 0; j--){
                g->board[i][j] = g->board[i][j - 1];
            }
            g->board[i][0] = empty;
        }
    }

}

short verifyDuplicates(Game *g, Block b, int lin, int col){
    int i = 1;
    //Verificar acima
    while((i <= lin) && g->board[lin - i][col].letter != '\0'){
        if((g->board[lin - i][col].letter == b.letter) && (g->board[lin - i][col].number == b.number)){
            return 0;
        }
        i++;
    }

    i = 1;

    //Verificar abaixo
    while((i <= (g->max_lin - lin)) && g->board[lin + i][col].letter != '\0'){
        if((g->board[lin + i][col].letter == b.letter) && (g->board[lin + i][col].number == b.number)){
            return 0;
        }
        i++;
    }

    i = 1;

    //Verificar a esquerda
    while((i <= col) && g->board[lin][col - i].letter != '\0'){
        if((g->board[lin][col - i].letter == b.letter) && (g->board[lin][col - i].number == b.number)){
            
            return 0;
        }
        
        i++;
    }

    i = 1;

    //Verificar a direita
    while((i <= (g->max_col - col)) && g->board[lin][col + i].letter != '\0'){
        if((g->board[lin][col + i].letter == b.letter) && (g->board[lin][col + i].number == b.number)){
            return 0;
        }
        i++;
    }

    return 1;
}

void verifyMoviment(Game *g, Block b, int lin, int col){
    //0: indefinido; 1: letra; 2: numero

    if(g->max_col == 0 && g->max_lin == 0){     //Primeira Rodada; Pode ser adicionado em qualquer local
        makeMoviment(g, b, lin, col);
    } else if(g->board[lin][col].letter != '\0'){
        invalidMove();
    } else {
        short isPossible_up = 0, isPossible_down = 0, isPossible_left = 0, isPossible_right = 0;
        Block up, down, left, right;

        short empty = 0;

        if(lin > 0) {
            up = g->board[lin - 1][col];
            if(up.letter == '\0'){
                isPossible_up = 1;
                empty++;
            }
        } else {
            isPossible_up = 1;
            empty++;
        }

        if(lin < g->max_lin) {
            down = g->board[lin + 1][col];
            if(down.letter == '\0'){
                isPossible_down = 1;
                empty++;
            }
        } else {
            isPossible_down = 1;
            empty++;
        }

        if(col > 0) {
            left = g->board[lin][col - 1];
            if(left.letter == '\0'){
                isPossible_left = 1;
                empty++;
            }
        } else {
            isPossible_left = 1;
            empty++;
        }

        if(col < g->max_col) {
            right = g->board[lin][col + 1];
            if(right.letter == '\0'){
                isPossible_right = 1;
                empty++;
            }
        } else {
            isPossible_right = 1;
            empty++;
        }

        if(empty < 4){
            if(isPossible_up == 0){                         //Nao vazio e existente
                if(up.relation.vertical == 0){
                    if(b.letter == up.letter){
                        b.relation.vertical = 1;
                        up.relation.vertical = 1;
                        isPossible_up = 1;
                    } else if(b.number == up.number) {
                        b.relation.vertical = 2;
                        up.relation.horizontal = 2;
                        isPossible_up = 1;
                    }
                } else if(up.relation.vertical == 1){
                    if(b.letter == up.letter){
                        b.relation.vertical = 1;
                        isPossible_up = 1;
                    }
                } else {
                    if(b.number == up.number){
                        b.relation.vertical = 2;
                        isPossible_up = 1;
                    }
                }
            }

            if(isPossible_down == 0){                         //Nao vazio e existente
                if(down.relation.vertical == 0){
                    if(b.letter == down.letter){
                        if(b.relation.vertical < 2){
                            b.relation.vertical = 1;
                            down.relation.vertical = 1;
                            isPossible_down = 1;
                        } 
                    } else if(b.number == down.number) {
                        if(b.relation.vertical != 1){
                            b.relation.vertical = 2;
                            down.relation.horizontal = 2;
                            isPossible_down = 1;
                        }
                    }
                } else if(down.relation.vertical == 1){
                    if(b.letter == down.letter){
                        if(b.relation.vertical < 2){
                            b.relation.vertical = 1;
                            isPossible_down = 1;
                        }
                    }
                } else {
                    if(b.number == down.number){
                        if(b.relation.vertical != 1){
                            b.relation.vertical = 2;
                            isPossible_down = 1;
                        }
                    }
                }
            }

            if(isPossible_left == 0){                         //Nao vazio e existente
                if(left.relation.horizontal == 0){
                    if(b.letter == left.letter){
                        b.relation.horizontal = 1;
                        left.relation.horizontal = 1;
                        isPossible_left = 1;
                    } else if(b.number == left.number) {
                        b.relation.horizontal = 2;
                        left.relation.horizontal = 2;
                        isPossible_left = 1;
                    }
                } else if(left.relation.horizontal == 1){
                    if(b.letter == left.letter){
                        b.relation.horizontal = 1;
                        isPossible_left = 1;
                    }
                } else {
                    if(b.number == left.number){
                        b.relation.horizontal = 2;
                        isPossible_left = 1;
                    }
                }
            }

            if(isPossible_right == 0){                         //Nao vazio e existente
                if(right.relation.horizontal == 0){
                    if(b.letter == right.letter){
                        if(b.relation.horizontal < 2){
                            b.relation.horizontal = 1;
                            right.relation.horizontal = 1;
                            isPossible_right = 1;
                        } 
                    } else if(b.number == right.number) {
                        if(b.relation.horizontal != 1){
                            b.relation.horizontal = 2;
                            right.relation.horizontal = 2;
                            isPossible_right = 1;
                        }
                    }
                } else if(right.relation.horizontal == 1){
                    if(b.letter == right.letter){
                        if(b.relation.horizontal < 2){
                            b.relation.horizontal = 1;
                            isPossible_right = 1;
                        }
                    }
                } else {
                    if(b.number == right.number){
                        if(b.relation.horizontal != 1){
                            b.relation.horizontal = 2;
                            isPossible_right = 1;
                        }
                    }
                }
            }

            if(isPossible_down == 1 && isPossible_up == 1 && isPossible_right == 1 && isPossible_left == 1){
                if(verifyDuplicates(g, b, lin, col)){
                    if(lin > 0){
                        g->board[lin - 1][col].relation.vertical = up.relation.vertical;
                    }
                    if(lin < g->max_lin) {
                        g->board[lin + 1][col].relation.vertical = down.relation.vertical;
                    }
                    if(col > 0) {
                        g->board[lin][col - 1].relation.horizontal = left.relation.horizontal;
                    }
                    if(col < g->max_col) {
                        g->board[lin][col + 1].relation.horizontal = right.relation.horizontal;
                    }
                    
                    makeMoviment(g, b, lin, col);
                } else {
                    invalidMove();
                }
            } else {
                invalidMove();
            }
        } else {
            invalidMove();
        }
    }
}

int playerTurn(Game *g, Player *players, short player_number){
    do {
        showBoard(g);
        showPlayersTiles(*g, players);

        //Imprime titulo
        printf("─────────────────────────────────────────────\n");
        green(1);
        printf("\tJOGADA DE @%s\n\n", players[player_number].name);
        
        //Mostra os blocos do jogador
        showOnePlayerTiles(players[player_number]);
        
        //Mostra as opcoes
        playerOptions();

        //Recebe o comando
        char command[40];
        fgets(command, 40, stdin);

        char *espaco = strchr(command, '\n');
        *espaco = '\0';

        //Encontra a primeira palavra
        char *cmd = strtok(command, " ");
        
        //verifica se o comando eh igual a "jogar"
        if(!strcmp(cmd, "jogar")){
            cmd = strtok(NULL, " ");
            
            Block b;
            if(strlen(cmd) == 2){
                if(cmd[0] >= 'A' && cmd[0] <= 'F' && cmd[1] >= '1' && cmd[1] <= '6'){
                    b.letter = cmd[0];
                    b.number = (short) atoi(&cmd[1]);
                    
                    if(verifyPlayerHand(players[player_number], b)){
                        cmd = strtok(NULL, " ");
                        
                        if(*cmd >= '0' && *cmd <= ('0' + g->max_lin)){
                            int lin = atoi(cmd);
                            
                            cmd = strtok(NULL, " ");
                            
                            if(*cmd >= '0' && *cmd <= ('0' + g->max_col)){
                                int col = atoi(cmd);
                                
                                b.relation.vertical = 0;
                                b.relation.horizontal = 0;
                                verifyMoviment(g, b, lin, col);
                            } else {
                                invalidPosition();
                            }
                        } else {
                            invalidPosition();
                        }
                    } else {
                        invalidBlock(1);
                    }
                } else {
                    invalidBlock(0);
                }
            } else {
                invalidBlock(0);
            }
        } else if(!strcmp(cmd, "passar")) {
            break;
        } else {
            invalidOption();
        }
    } while (1);
}

void gameRounds(Game *g, Player *p){
    short result = 0;

    int i = 0;
    while(!result){
        playerTurn(g, p, i);
        i = (++i) % (g->n_players);
    }
}
