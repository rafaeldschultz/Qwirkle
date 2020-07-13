#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "headers/infoBlock.h"
#include "headers/infoGame.h"
#include "headers/infoPlayer.h"
#include "headers/infoMove.h"

#include "headers/colors.h"
#include "headers/output.h"
#include "headers/buffer.h"
#include "headers/blocks.h"
#include "headers/board.h"
#include "headers/players.h"
#include "headers/pontuacao.h"

#include "headers/game.h"

/******************************************
 * INICIALIZA OU DELETA ELEMENTOS DO JOGO *
 ******************************************/

/*
 * Inicializa o Jogo
 */
void createGame(Game *g, Player **p){
    createBoard(g);
    createBag(g);
    initializePlayers(g, p);
}

/*
 * Deleta os Elementos do Jogo
 */
void deleteGame(Game *g, Player **p){
    deleteBlocksControl(g);
    deletePlayers(*g, *p);
    eraseBoard(g);
}

/***********
 * RODADAS *
 ***********/

/*
 * Inicia o jogo e mantem a alternancia de jogadores durante as rodadas
 */
void gameRounds(Game *g, Player *p){ 
    do{
        cheatModeMenu();                                    //Verifica se o cheatMode deve ser ativado
        char isCheatMode = fgetc(stdin);
        cleanBufferEnter();                                 //limpa o buffer de entrada ate um enter

        if(isCheatMode == 's' || isCheatMode == 'n') {      //Se a resposta for dada minuscula (apenas as opcoes aceitas), transforma em maiuscula
            isCheatMode -= 32;
        }
    
        if(isCheatMode == 'S' || isCheatMode == 'N'){       //Verifica se a opcao eh valida
            short result = 0;                               //armazena se o resultado do jogo ja foi definido

            int i = 0;
            while(!result){                                 //Executa ate que o resultado do jogo seja definido
                playerTurn(g, p, i, isCheatMode);           //Executa a vez de um jogador      
                i = (++i) % (g->n_players);                 //Soma um ao contador de usuario e realiza o modulo com o numero de jogadores

                if(g->bag.blocks_number == 0){              //se a quantidade de pecas na sacola for 0
                    result = verifyEndGame(g, p);           //verifica se o jogo finalizou
                }
            }
            break;                                          //Quando finalizar o jogo, quebra o laco de repeticao
        } else {
            invalidOption(0);                               //indica opcao invalida
        }
    } while(1);
}

/*
 * Realiza a vez de um jogador
 */
void playerTurn(Game *g, Player *players, short player_number, char isCheatMode){
    short p_option = 0;                          //Define o tipo de jogada selecionada (1:'jogar'; 2:'trocar')
    short line_turn = 0;                         //Indica o sentido da jogada (0: indefinido; 1: linha; 2: coluna)
    
    int score = 0;                               //Armazena a pontuacao da jogada

    Move firstMove;                              //Armazena as coordenadas do primeiro movimento feito pelo jogador na rodada
    firstMove.col = -1;
    firstMove.lin = -1;

    do {
        showBoard(g);
        showPlayersTiles(*g, players);

        //Imprime titulo
        printf("───────────────────────────────────────────────────\n");
        green(1);
        printf("\tJOGADA DE @%s\n\n", players[player_number].name);         //Indica o Jogador da vez
        
        //Mostra os blocos do jogador
        showOnePlayerTiles(players[player_number]);                     //Mostra os blocos do jogador da vez
        
        //Mostra as opcoes
        playerOptions();                                                //Mostra as opcoes para o jogador
        
        do{
            blue(1);
            printf("Selecione:   ");
            reset();

            //Recebe o comando
            char command[40];
            fgets(command, 40, stdin);

            char *enter = strchr(command, '\n');                            //Encontra o enter adicionado ao final pelo fgets
            if(enter != NULL) *enter = '\0';                                //Remove o enter se ele existir

            //Encontra os comandos
            char *cmd = strtok(command, " ");
            char *peca = strtok(NULL, " ");
            char *lin = strtok(NULL, " ");
            char *col = strtok(NULL, " ");
            
            if(cmd != NULL && (!strcmp(cmd, "jogar") || !strcmp(cmd, "j"))){    //Verifica se a opcao eh jogar
                Block b;
                if(peca != NULL && strlen(peca) == 2){                          //Verifica se o bloco inserido eh valido
                    if(peca[0] >= 'a' && peca[0] <= 'f'){                       //Verifica se a letra eh minuscula e converte para maiuscula
                        peca[0] -= 32;
                    }
                    if(peca[0] >= 'A' && peca[0] <= 'F' && peca[1] >= '1' && peca[1] <= '6'){   //verifica se o bloco apresenta numero/letra validos
                        b.letter = peca[0];                                     //Cria uma struct bloco com as informacoes passadas
                        b.number = (short) atoi(&peca[1]);
                        b.relation.vertical = 0;
                        b.relation.horizontal = 0;

                        Move m;                                                 
                        if((lin != NULL && isdigit(lin[0])) && ((col != NULL && isdigit(col[0])))){     //verifica se linha e coluna inseridos sao validos
                            m.lin = (short) atoi(lin);
                            m.col = (short) atoi(col);

                            if((m.col >= 0) && (m.lin >= 0) && (m.col <= g->max_col) && (m.lin <= g->max_lin)){     //Verifica se linha e coluna estao no intervalo permitido pelo tabuleiro
                                if(p_option == 0 || p_option == 1){                                     //Verifica se outro tipo de jogada nao foi executada antes
                                    short m_status = 0;                                                 //Representa se a jogada foi realizada com sucesso
                                    if(isCheatMode == 'S'){                                             //Verifica se o cheatMode esta ativado
                                        m_status = useBlockCheatMode(g, &players[player_number], b, m, &firstMove, &line_turn);     //verifica a jogada eh valida e faz o movimento se sim
                                    } else {
                                        m_status = useBlock(g, &players[player_number], b, m, &firstMove, &line_turn);
                                    }

                                    if(m_status){                               //Verifica se a jogada foi executada com sucesso
                                        p_option = 1;
                                        if(line_turn == 1){
                                            if(g->board[m.lin][m.col].relation.vertical != 0){
                                                score += defineScoreUp(g, m) + defineScoreDown(g, m) - 1;
                                            }
                                        }
                                        break;
                                    }
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
                        invalidBlock(0);
                    }   
                } else {
                    invalidBlock(0);
                }
            } 
            else if(cmd != NULL && (!strcmp(cmd, "trocar") || !strcmp(cmd, "t"))){
                Block b;
                if(peca != NULL && strlen(peca) == 2){                          //Verifica se o bloco inserido eh valido
                    if(peca[0] >= 'a' && peca[0] <= 'f'){                       //Verifica se a letra eh minuscula e converte para maiuscula
                        peca[0] -= 32;
                    }
                    if(peca[0] >= 'A' && peca[0] <= 'F' && peca[1] >= '1' && peca[1] <= '6'){   //verifica se o bloco apresenta numero/letra validos
                        b.letter = peca[0];                                     //Cria uma struct bloco com as informacoes passadas
                        b.number = (short) atoi(&peca[1]);
                        b.relation.vertical = 0;
                        b.relation.horizontal = 0;
                        
                        if(p_option == 0 ||  p_option == 2){                    //verifica se o usuario ja fez uma jogada de outro tipo
                            short t_status = exchangeBlock(g, &players[player_number], b);  //Troca a peca
                            
                            if(t_status){                                       //Verifica se a peca foi trocada corretamente
                                p_option = 2;
                                break;
                            }
                        } else {
                            invalidOption(1);
                        } 
                    } else {
                        invalidBlock(0);
                    }   
                } else {
                    invalidBlock(0);
                }
            } else if((!strcmp(cmd, "passar")) || (!strcmp(cmd, "p"))) {        //verifica se a opcao eh passar
                if(g->bag.blocks_number > 0){                                   //verifica se existem pecas na sacola disponiveis
                    completeBlocksNumber(g, &players[player_number]);           //se sim, completa com as pecas que faltam
                }
                score += defineScoreFirstMove(g, firstMove);

                if(!((g->board[firstMove.lin][firstMove.col].relation.horizontal != 0) && (g->board[firstMove.lin][firstMove.col].relation.vertical != 0))){
                    score--;
                }
                
                printf("SCORE: %d\n", score);

                players[player_number].score += score;
                return;
            } else {
                invalidOption(0);
            }
        } while (1);
    } while (1);
}


/********************
 * OPCOES DE JOGADA *
 ********************/

/*
 * Coloca uma peca no tabuleiro quando em cheatMode
 */
short useBlockCheatMode(Game *g, Player *p, Block b, Move m, Move *firstMove, short *lt){
    short mov_status = verifyMoviment(g, b, m, firstMove, lt);        //verifica a possibilidade de executar o movimento
                                                                      //se possivel, ja executa
    if(mov_status){                     //Verifica se o movimento foi executado
        removeBlockFromHand(p, b);      //remove o bloco utilizado da mao do jogador
        return 1;
    }

    return 0;
}

/*
 * Coloca uma peca no tabuleiro quando em modo normal
 */
short useBlock(Game *g, Player *p, Block b, Move m, Move *firstMove, short *lt){
    if(verifyPlayerHand(*p, b)){            //Verifica se o bloco existe na mao do jogador
        short mov_suc = verifyMoviment(g, b, m, firstMove, lt);       //verifica a possibilidade de executar o movimento
                                                                      //se possivel, ja executa
        if(mov_suc){                        //Verifica se o movimento foi executado
            removeBlockFromHand(p, b);      //remove o bloco utilizado da mao do jogador
            return 1;
        }               
    } else {
        invalidBlock(1);
    }
    return 0;
}

/*
 * Troca um bloco do usuario
 */
short exchangeBlock(Game *g, Player *p, Block b){
    if(g->bag.blocks_number > 0){                               //Verifica se ainda ha pecas disponiveis no saco
        if(verifyPlayerHand(*p, b)){                            //verifica se o usuario possui a peca
            changeBlock(g, p, b);                               //troca o bloco                           
            return 1;
        } else {
            invalidBlock(1);
        }
    } else {                                                    //Senao houver mais pecas no saco, informa para o usuario
        noMoreBlocksBag();
    }
    
    return 0;
}


/****************
 * VERIFICACOES *
 ****************/

/*
 * Verifica se um movimento eh possivel
 * Armazena algumas verificacoes mais simples e trabalhosas
 * Porta de entrada para outras funcoes de verificacao
 */
short verifyMoviment(Game *g, Block b, Move m, Move *firstMove, short *lt){
    //0: indefinido; 1: letra; 2: numero

    if(g->max_col == 0 && g->max_lin == 0){                     //Primeira Rodada; Pode ser adicionado em qualquer local
        firstMove->col = m.col;                                 //altera as coordenadas de coluna do primeiro movimento
        firstMove->lin = m.lin;                                 //altera as coordenadas de linha do primeiro movimento
        makeMoviment(g, b, m, firstMove);
        return 1;
    } else if(g->board[m.lin][m.col].letter != '\0'){           //Verifica se a posicao inserida para o movimento eh vazia
        invalidMove();
        return 0;
    } else if(firstMove->lin != -1 && firstMove->col != -1){    //Verifica se as coordenadas do primeiro movimento foram setadas
        if(*lt == 1 && m.lin != firstMove->lin){                //verifica se o criterio da rodada do usuario eh mesma LINHA e a linha inserida eh diferente da primeira jogada
            invalidMove();                                      //imprime mensagem de erro
            return 0;
        } else if(*lt == 2 && m.col != firstMove->col){         //verifica se o criterio da rodada do usuario eh mesma COLUNA e a coluna inserida eh diferente da primeira jogada
            invalidMove();                                      //imprime mensagem de erro
            return 0;
        } else if(*lt == 0 && !(firstMove->col == m.col || firstMove->lin == m.lin)){   //verifica se o criterio da rodada do usuario eh INDEFINIDO e a coluna/linha inserida eh diferente da primeira jogada
            invalidMove();                                      //imprime mensagem de erro
            return 0;
        }
       
        if(!verifySameLine(g, m, *firstMove)){                  //verifica se a primeira peca e a peca da jogada atual estao em uma mesma linha
            invalidMove();                                      //imprime mensagem de erro
            return 0;
        }
    } 

    short isPossible_up = 0, isPossible_down = 0, isPossible_left = 0, isPossible_right = 0;    //indicam a possibilidade de jogada em cada uma das direcoes
    Block up, down, left, right;                                //indicam os blocos ao redor da posicao indica em m

    short empty = 0;                                            //indica quantos blocos ao redor estao vazios

    if(m.lin > 0) {                                 //Verifica se a linha indicada eh maior que 0
        up = g->board[m.lin - 1][m.col];            //atribui a peca acima a up
        if(up.letter == '\0'){                      //verifica se ela eh vazia
            isPossible_up = 1;                      //Se sim, indica que a ha possibilidade de adicao nas coordenadas m
            empty++;
        }
    } else {                                        //Se for igual a 0, automaticamente eh vazia (borda do tabuleiro)
        isPossible_up = 1;
        empty++;
    }

    if(m.lin < g->max_lin) {                        //Verifica se a linha indicada eh menor que o max do tabuleiro
        down = g->board[m.lin + 1][m.col];          //atribui a peca abaixo a down
        if(down.letter == '\0'){                    //verifica se ela eh vazia
            isPossible_down = 1;                    //Se sim, indica que a ha possibilidade de adicao nas coordenadas m
            empty++;
        }
    } else {
        isPossible_down = 1;                        //Se for igual ao max do tabuleiro, automaticamente eh vazia (borda do tabuleiro)
        empty++;
    }

    if(m.col > 0) {                                 //Verifica se a coluna indicada eh maior que 0
        left = g->board[m.lin][m.col - 1];          //atribui a peca a esquerda a left
        if(left.letter == '\0'){                    //verifica se ela eh vazia
            isPossible_left = 1;                    //Se sim, indica que a ha possibilidade de adicao nas coordenadas m
            empty++;
        }
    } else {                                        //Se for igual a 0, automaticamente eh vazia (borda do tabuleiro)
        isPossible_left = 1;
        empty++;
    }

    if(m.col < g->max_col) {                        //Verifica se a coluna indicada eh menor que o max do tabuleiro
        right = g->board[m.lin][m.col + 1];         //atribui a peca a direita a right
        if(right.letter == '\0'){                   //verifica se ela eh vazia
            isPossible_right = 1;                   //Se sim, indica que a ha possibilidade de adicao nas coordenadas m
            empty++;
        }
    } else {
        isPossible_right = 1;                       //Se for igual a 0, automaticamente eh vazia (borda do tabuleiro)
        empty++;
    }

    short duplicatedVertical = 1, duplicatedHorizontal = 1;

    if(isPossible_down == 0 && isPossible_up == 0){                     //Verifica se eh possivel ocorrer a uniao de duas linhas
       duplicatedVertical = verifyDuplicatesJoinedVertical(g, m);       //Verifica se havera duplifcados na vertical caso a juncao ocorra
    }

    if(isPossible_left == 0 && isPossible_right == 0){                  //Verifica se eh possivel ocorrer a uniao de duas linhas
        duplicatedHorizontal = verifyDuplicatesJoinedHorizontal(g, m);  //Verifica se havera duplifcados na horizontal caso a juncao ocorra
    }

    if(duplicatedVertical && duplicatedHorizontal){         //Verifica se nao existe a possibilidade de duplicadas caso ocorra uniao de linhas/colunas
        if(empty < 4){                                      //Verifica se a peca nao esta isolada
            if(isPossible_up == 0){                         //Nao vazio e existente
                if(up.relation.vertical == 0){              //verifica se a relacao da peca super na vertical ja foi definida
                    if(b.letter == up.letter){              //Senao, se a letra coincidir com b define a relacao para 1
                        b.relation.vertical = 1;
                        up.relation.vertical = 1;
                        isPossible_up = 1;
                    } else if(b.number == up.number) {      //Senao, se o numero coincidir com b define a relacao para 1
                        b.relation.vertical = 2;            
                        up.relation.horizontal = 2;
                        isPossible_up = 1;
                    }
                } else if(up.relation.vertical == 1){       //Se estiver definida como 1, verifica se as letras coincidem
                    if(b.letter == up.letter){
                        b.relation.vertical = 1;
                        isPossible_up = 1;
                    }  
                } else {                                    //Caso contrario (se estiver definida como 2), verifica se os numeros coincidem
                    if(b.number == up.number){
                        b.relation.vertical = 2;
                        isPossible_up = 1;
                    }
                }
            }
            
            /*
             * Ideia semelhante ao de cima, mas para o bloco debaixo
             */
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

            /*
             * Ideia semelhante ao de cima, mas para o bloco da esquerda
             */
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

            /*
             * Ideia semelhante ao de cima, mas para o bloco da direita
             */
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

            /*
             * Verifica se existe possibilidade de adicao nas 4 direcoes
             */
            if(isPossible_down == 1 && isPossible_up == 1 && isPossible_right == 1 && isPossible_left == 1){
                
                if(verifyDuplicates(g, b, m)){          //Verifica se ira existir duplicadas na linha que sera inserida
                    if(m.lin > 0){                      //Senao, verifica se a linha da jogada eh maior que 0
                        g->board[m.lin - 1][m.col].relation.vertical = up.relation.vertical;    //Se sim, atribui a nova relacao ao bloco acima
                    }
                    if(m.lin < g->max_lin) {            //Verifica se a linha da jogada eh menor que a linha max do tabuleiro
                        g->board[m.lin + 1][m.col].relation.vertical = down.relation.vertical;  //Se sim, atribui a nova relacao ao bloco abaixo
                    }
                    if(m.col > 0) {                     //Verifica se a coluna da jogada eh maior que 0
                        g->board[m.lin][m.col - 1].relation.horizontal = left.relation.horizontal;  //Se sim, atribui a nova relacao ao bloco a esquerda
                    }
                    if(m.col < g->max_col) {            //Verifica se a coluna da jogada eh menor que a coluna max do tabuleiro
                        g->board[m.lin][m.col + 1].relation.horizontal = right.relation.horizontal; //Se sim, atribui a nova relacao ao bloco a direita
                    }
                    
                    if(firstMove->col == -1 && firstMove->lin == -1){       //Verifica se o primeiro movimento da jogada esta indefinido
                        firstMove->col = m.col;                             //Se sim, esse eh o primeiro movimento
                        firstMove->lin = m.lin;
                    } else if(*lt == 0){                                    //Verifica se a linha da jogada eh indefinida
                        if(firstMove->lin == m.lin){                        //Se sim, atribui a semelhanca do primeiro movimento com esse como a linha da jogada
                            *lt = 1;                                        //1: mesma linha
                        } else {
                            *lt = 2;                                        //2: mesma coluna
                        }
                    }

                    makeMoviment(g, b, m, firstMove);                       //Realiza o movimento
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

/*
 * Verifica se a peca b ja existe na linha em que sera adicionada
 */
short verifyDuplicates(Game *g, Block b, Move m){
    int i = 1;
    
    //Verificar letras duplicadas acima da posicao indicada em m
    while((i <= m.lin) && g->board[m.lin - i][m.col].letter != '\0'){                   
        if((g->board[m.lin - i][m.col].letter == b.letter) && (g->board[m.lin - i][m.col].number == b.number)){
            return 0;
        }
        i++;
    }

    i = 1;

    //Verifica letras duplicadas abaixo da posicao indicada em m
    while((i <= (g->max_lin - m.lin)) && g->board[m.lin + i][m.col].letter != '\0'){
        if((g->board[m.lin + i][m.col].letter == b.letter) && (g->board[m.lin + i][m.col].number == b.number)){
            return 0;
        }
        i++;
    }

    i = 1;

    //Verifica letras duplicadas a esquerda da posicao indicada em m
    while((i <= m.col) && g->board[m.lin][m.col - i].letter != '\0'){
        if((g->board[m.lin][m.col - i].letter == b.letter) && (g->board[m.lin][m.col - i].number == b.number)){
            
            return 0;
        }
        
        i++;
    }

    i = 1;

    //Verifica letras duplicadas a direita da posicao indicada em m
    while((i <= (g->max_col - m.col)) && g->board[m.lin][m.col + i].letter != '\0'){
        if((g->board[m.lin][m.col + i].letter == b.letter) && (g->board[m.lin][m.col + i].number == b.number)){
            return 0;
        }
        i++;
    }

    return 1;
}

/*
 * Realiza um movimento que ja foi verificado e eh possivel
 */
int makeMoviment(Game *g, Block b, Move m, Move *firstMove){
    g->board[m.lin][m.col] = b;

    Block empty;                                //Cria um bloco vazio
    empty.letter = '\0';
    empty.number = 0;
    empty.relation.horizontal = 0;
    empty.relation.vertical = 0;

    /*
     * Verifica se a linha indicada em m eh igual a linha max
     * Se sim, utiliza realloc para aumentar o tabuleiro
     */
    if(m.lin == g->max_lin){                    
        g->max_lin++;
        g->board = (Block **) realloc(g->board, (g->max_lin + 1) * sizeof(Block *));
        g->board[g->max_lin] = (Block *) calloc(g->max_col + 1, sizeof(Block));
    }

    /*
     * Verifica se a linha indicada em m eh igual a 0
     * Se sim, utiliza realloc para aumentar o tabuleiro
     */
    if(m.lin == 0){
        g->max_lin++;
        g->board = (Block **) realloc(g->board, (g->max_lin + 1) * sizeof(Block *));
        g->board[g->max_lin] = (Block *) calloc(g->max_col + 1, sizeof(Block));

        Block *temp = g->board[g->max_lin];

        for(short i = g->max_lin; i > 0; i--){      //Move todo o tabuleiro para baixo
            g->board[i] = g->board[i - 1];
        }
        
        g->board[0] = temp; 
        (firstMove->lin)++;                         //Move a posicao do primeiro movimento para baixo
    }

    /*
     * Verifica se a coluna indicada em m eh igual a coluna max
     * Se sim, utiliza realloc para aumentar o tabuleiro
     */
    if(m.col == g->max_col){
        g->max_col++;
        
        for(short i = 0; i < g->max_lin + 1; i++){
            g->board[i] = (Block *) realloc(g->board[i], (g->max_col + 1) * sizeof(Block));
            g->board[i][g->max_col] = empty;
        }
    }

    /*
     * Verifica se a coluna indicada em m eh igual a 0
     * Se sim, utiliza realloc para aumentar o tabuleiro
     */
    if(m.col == 0){
        g->max_col++;
        
        for(short i = 0; i < g->max_lin + 1; i++){
            g->board[i] = (Block *) realloc(g->board[i], (g->max_col + 1) * sizeof(Block));
            for(short j = g->max_col; j > 0; j--){      //move as colunas para a direita
                g->board[i][j] = g->board[i][j - 1];
            }
            g->board[i][0] = empty;   
        }
        (firstMove->col)++;                             //Move a posicao do primeiro movimento para direita
    }
}

/*
 * Verifica por duplicadas caso haja possibilidade de duas linhas verticais serem unidas
 */
short verifyDuplicatesJoinedVertical(Game *g, Move m){
    short i = 1;

    Block b[10];                            //5 acima e 5 abaixo da peça (maximo)

    //Adiciona as pecas acima da posicao definida por m ao vetor b
    while((m.lin - i >= 0) && (g->board[m.lin - i][m.col].letter != '\0')){
        b[i - 1] = g->board[m.lin - i][m.col];
        i++;
    }

    short j = i - 1;
    i = 1;

    //Adiciona as pecas abaixo da posicao definida por m ao vetor b
    while((m.lin + i <= g->max_lin) && (g->board[m.lin + i][m.col].letter != '\0')){
        b[j] = g->board[m.lin + i][m.col];
        j++;
        i++;
    }

    //Verifica se existe algum repetido
    for(i = 0; i < j; i++){
        for(short k = i + 1; k < j; k++){
            if((b[i].letter == b[k].letter) && (b[i].number == b[k].number)){
                return 0;                       //Se sim, retorna 0
            }
        } 
    }
    return 1;
}

/*
 * Verifica por duplicadas caso haja possibilidade de duas linhas horizontais serem unidas
 */
short verifyDuplicatesJoinedHorizontal(Game *g, Move m){
    short i = 1;

    Block b[10]; //5 acima e 5 abaixo da peça

    //Adiciona as pecas a esquerda da posicao definida por m ao vetor b
    while((m.col - i >= 0) && (g->board[m.lin][m.col - i].letter != '\0')){
        b[i - 1] = g->board[m.lin][m.col - i];
        i++;
    }

    short j = i - 1;
    i = 1;

    //Adiciona as pecas a direita da posicao definida por m ao vetor b
    while((m.col + i <= g->max_col) && (g->board[m.lin][m.col + i].letter != '\0')){
        b[j] = g->board[m.lin][m.col + i];
        j++;
        i++;
    }

    //Verifica se existe algum repetido
    for(i = 0; i < j; i++){
        for(short k = i + 1; k < j; k++){
            if((b[i].letter == b[k].letter) && (b[i].number == b[k].number)){
                return 0;                   //Se sim, retorna 0
            }
        } 
    }
    return 1;
}

/*
 * Verifica se uma peca em uma jogada esta na mesma linha da primeira peca jogada na vez de um dos jogadores
 */
short verifySameLine(Game *g, Move m, Move firstMove){
    Block first = g->board[firstMove.lin][firstMove.col];
    
    //Se as linhas de m e firstMove forem iguais
    if(firstMove.lin == m.lin){

        /*
         * Se m.col > firstMove.col, verifica as pecas a esquerda da posicao m 
         * Se encontrar a peca presente em firstMove antes de uma vazia, esta na mesma linha
         */
        if(m.col > firstMove.col){ 
            while(g->board[m.lin][m.col - 1].letter != '\0'){
                if((g->board[m.lin][m.col - 1].letter == first.letter) && (g->board[m.lin][m.col - 1].number == first.number)){
                    return 1;
                }
                m.col--;
            }
        } else {
            /*
            * Se m.col < firstMove.col, verifica as pecas a direita da posicao m 
            * Se encontrar a peca presente em firstMove antes de uma vazia, esta na mesma linha
            */
            while(g->board[m.lin][m.col + 1].letter != '\0'){
                if((g->board[m.lin][m.col + 1].letter == first.letter) && (g->board[m.lin][m.col + 1].number == first.number)){
                    return 1;
                }
                m.col++;
            }
        }
    } else {
        /*
        * Se m.lin > firstMove.lin, verifica as pecas acima da posicao m 
        * Se encontrar a peca presente em firstMove antes de uma vazia, esta na mesma linha
        */
        if(m.lin > firstMove.lin){
            while(g->board[m.lin - 1][m.col].letter != '\0'){
                if((g->board[m.lin - 1][m.col].letter == first.letter) && (g->board[m.lin - 1][m.col].number == first.number)){
                    return 1;
                }
                m.lin--;
            }
        } else {
            /*
            * Se m.lin < firstMove.lin, verifica as pecas abaixo da posicao m 
            * Se encontrar a peca presente em firstMove antes de uma vazia, esta na mesma linha
            */
            while(g->board[m.lin + 1][m.col].letter != '\0'){
                if((g->board[m.lin + 1][m.col].letter == first.letter) && (g->board[m.lin + 1][m.col].number == first.number)){
                    return 1;
                }
                m.lin++;
            }
        }
    }
    return 0;
}

/*
 * Verifica se o jogo finalizou
 */
int verifyEndGame(Game *g, Player *players){
    for(short i = 0; i < g->n_players; i++){        // verifica todos os jogadores
        short j;
        for(j = 0; j < HAND_LENGTH; j++){
            if(players[i].tiles[j].letter != '\0'){ //Verifica se as peças do jogador sao vazias
                break;
            }
        }
        if(j == HAND_LENGTH){                       //se o contador for igual a quantidade de pecas na mao do jogador (padrao: 6), existe um vencedor
            return 1;
        }
    }
    return 0;
}
