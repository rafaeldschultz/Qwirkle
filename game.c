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

int makeMoviment(Game *g, Block b, int lin, int col, short *f_lin, short *f_col){
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
        (*f_lin)++;
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
        (*f_col)++;
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

short verifyDuplicatesJoinedVertical(Game *g, int lin, int col){
    short i = 1;

    Block b[10]; //5 acima e 5 abaixo da peça

    //Acima
    while((lin - i >= 0) && (g->board[lin - i][col].letter != '\0')){
        b[i - 1] = g->board[lin - i][col];
        i++;
    }

    short j = i - 1;
    i = 1;

    //Abaixo
    while((lin + i <= g->max_lin) && (g->board[lin + i][col].letter != '\0')){
        b[j] = g->board[lin + i][col];
        j++;
        i++;
    }

    for(i = 0; i < j; i++){
        for(short k = i + 1; k < j; k++){
            if((b[i].letter == b[k].letter) && (b[i].number == b[k].number)){
                return 0;
            }
        } 
    }
    return 1;
}

short verifyDuplicatesJoinedHorizontal(Game *g, int lin, int col){
    short i = 1;

    Block b[10]; //5 acima e 5 abaixo da peça

    //A esquerda
    while((col - i >= 0) && (g->board[lin][col - i].letter != '\0')){
        b[i - 1] = g->board[lin][col - i];
        i++;
    }

    short j = i - 1;
    i = 1;

    //A direita
    while((col + i <= g->max_col) && (g->board[lin][col + i].letter != '\0')){
        b[j] = g->board[lin][col + i];
        j++;
        i++;
    }

    for(i = 0; i < j; i++){
        for(short k = i + 1; k < j; k++){
            if((b[i].letter == b[k].letter) && (b[i].number == b[k].number)){
                return 0;
            }
        } 
    }
    return 1;
}

short verifyMoviment(Game *g, Block b, int lin, int col, short *f_lin, short *f_col, short *lt){
    //0: indefinido; 1: letra; 2: numero

    if(g->max_col == 0 && g->max_lin == 0){     //Primeira Rodada; Pode ser adicionado em qualquer local
        *f_col = col;
        *f_lin = lin; 
        makeMoviment(g, b, lin, col, f_lin, f_col);
        return 1;
    } else if(g->board[lin][col].letter != '\0'){
        invalidMove();
        return 0;
    } else if(*f_lin != -1 && *f_col != -1){
        if(*lt == 1 && lin != *f_lin){
            invalidMove();
            return 0;
        } else if(*lt == 2 && col != *f_col){
            invalidMove();
            return 0;
        } else if(*lt == 0 && !(*f_col == col || *f_lin == lin)){
            invalidMove();
            return 0;
        }
        
    } 

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

    short duplicatedVertical = 1, duplicatedHorizontal = 1;

    if(isPossible_down == 0 && isPossible_up == 0){
       duplicatedVertical = verifyDuplicatesJoinedVertical(g, lin, col);
    }

    if(isPossible_left == 0 && isPossible_right == 0){
        duplicatedHorizontal = verifyDuplicatesJoinedHorizontal(g, lin, col);
    }

    if(duplicatedVertical && duplicatedHorizontal){
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
                    
                    if(*f_col == -1 && *f_lin == -1){
                        *f_col = col;
                        *f_lin = lin;
                    } else if(*lt == 0){
                        if(*f_lin == lin){
                            *lt = 1;
                        } else {
                            *lt = 2;
                        }
                    }

                    makeMoviment(g, b, lin, col, f_lin, f_col);
                    return 1;
                } else {
                    invalidMove();
                }
            } else {
                invalidMove();
            }
        } else {
            invalidMove();
        }
    } else {
        invalidMove();
    }

    return 0;
}

int playerTurn(Game *g, Player *players, short player_number, char isCheatMode){
    short p_option = 0;                          //Define se o tipo de jogada selecionada
    short line_turn = 0;                         //0: indefinido; 1: linha; 2: coluna.
    
    short firstMove_col = -1;
    short firstMove_lin = -1;

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
                    
                    if(isCheatMode == 'S'){
                        cmd = strtok(NULL, " ");
                            
                        if(*cmd >= '0' && *cmd <= ('0' + g->max_lin)){
                            int lin = atoi(cmd);
                            
                            cmd = strtok(NULL, " ");
                            
                            if(*cmd >= '0' && *cmd <= ('0' + g->max_col)){
                                int col = atoi(cmd);
                                
                                if(p_option == 0 || p_option == 1){
                                    b.relation.vertical = 0;
                                    b.relation.horizontal = 0;
                                    
                                    short mov_suc = verifyMoviment(g, b, lin, col, &firstMove_lin, &firstMove_col, &line_turn);

                                    if(mov_suc){
                                        removeBlockFromHand(players, player_number, b);
                                    }
                                    p_option = 1;
                                } else {
                                    invalidOption(1);
                                }
                            } else {
                                invalidPosition();
                            }
                        } else {
                            invalidPosition();
                        }
                    } else {
                        if(verifyPlayerHand(players[player_number], b)){
                            cmd = strtok(NULL, " ");
                            
                            if(*cmd >= '0' && *cmd <= ('0' + g->max_lin)){
                                int lin = atoi(cmd);
                                
                                cmd = strtok(NULL, " ");
                                
                                if(*cmd >= '0' && *cmd <= ('0' + g->max_col)){
                                    int col = atoi(cmd);
                                    
                                    if(p_option == 0 || p_option == 1){
                                        b.relation.vertical = 0;
                                        b.relation.horizontal = 0;
                                        short mov_suc = verifyMoviment(g, b, lin, col, &firstMove_lin, &firstMove_col, &line_turn);
                                        
                                        if(mov_suc){
                                            removeBlockFromHand(players, player_number, b);
                                        }
                                        p_option = 1;
                                    } else {
                                        invalidOption(1);
                                    }
                                } else {
                                    invalidPosition();
                                }
                            } else {
                                invalidPosition();
                            }
                        } else {
                            invalidBlock(1);
                        }
                    }
                } else {
                    invalidBlock(0);
                }
            } else {
                invalidBlock(0);
            }
        } else if(!strcmp(cmd, "trocar")){
            cmd = strtok(NULL, " ");

            Block b;
            if(strlen(cmd) == 2){
                if(cmd[0] >= 'A' && cmd[0] <= 'F' && cmd[1] >= '1' && cmd[1] <= '6'){
                    b.letter = cmd[0];
                    b.number = (short) atoi(&cmd[1]);
                    
                    if(verifyPlayerHand(players[player_number], b)){
                        if(p_option == 0 ||  p_option == 2){
                            changeBlock(g, players, player_number, b);
                            p_option = 2;
                        } else {
                            invalidOption(1);
                        }
                    } else {
                        invalidBlock(1);
                    }
                } else {
                    invalidBlock(0);
                }
            }
        } else if(!strcmp(cmd, "passar")) {
            completeBlocksNumber(g, players, player_number);
            break;
        } else {
            invalidOption(0);
        }
    } while (1);
}

void gameRounds(Game *g, Player *p){ 
    do{
        cheatModeMenu();
        char isCheatMode = fgetc(stdin);
        cleanBufferEnter();
        if(isCheatMode == 's' || isCheatMode == 'n') {
            isCheatMode -= 32;
        }
    
        if(isCheatMode == 'S' || isCheatMode == 'N'){
            short result = 0;

            int i = 0;
            while(!result){
                playerTurn(g, p, i, isCheatMode);
                i = (++i) % (g->n_players);
            }
            break;
        } else {
            invalidOption(0);
        }
    } while(1);
}
