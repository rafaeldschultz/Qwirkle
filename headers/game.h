#include "infoPlayer.h"
#include "infoGame.h"
#include "infoMove.h"

/******************************************
 * INICIALIZA OU DELETA ELEMENTOS DO JOGO *
 ******************************************/
void createGame(Game *g, Player **p);
void deleteGame(Game *g, Player **p);

/***********
 * RODADAS *
 ***********/
void gameRounds(Game *g, Player *p);
void playerTurn(Game *g, Player *players, short player_number, char isCheatMode);

/********************
 * OPCOES DE JOGADA *
 ********************/
short useBlockCheatMode(Game *g, Player *p, Block b, Move v, Move *firstMove, short *lt);
short useBlock(Game *g, Player *p, Block b, Move m, Move *firstMove, short *lt);
short exchangeBlock(Game *g, Player *p, Block b);

/****************
 * VERIFICACOES *
 ****************/
short verifyMoviment(Game *g, Block b, Move m, Move *firstMove, short *lt);
short verifyDuplicates(Game *g, Block b, Move m);
short verifyDuplicatesJoinedVertical(Game *g, Move m);
short verifyDuplicatesJoinedHorizontal(Game *g, Move m);
short verifySameLine(Game *g, Move m, Move firstMove);
int verifyEndGame(Game *g, Player *players);

/*************
 * MOVIMENTO *
 *************/
int makeMoviment(Game *g, Block b, Move m, Move *firstMove);
