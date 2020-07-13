#include "infoGame.h"
#include "infoPlayer.h"


/*************
 * CONVERSAO *
 *************/
void numberToColor(short n);


/***************
 * BOAS-VINDAS *
 ***************/
void welcome();


/*********************
 * MENSAGENS DE ERRO *
 *********************/
void invalidNumberPlayers();
void errorAllocation();
void noMoreBlocksBag();
void invalidMove();
void invalidBlock(short a);
void invalidPosition();
void invalidOption(short n);


/*********
 * MENUS *
 *********/
void playerOptions();
void cheatModeMenu();


/******************
 * MOSTRAR BLOCOS *
 ******************/
void showBoard(Game * g);
void showPlayersTiles(Game g, Player *players);
void showOnePlayerTiles(Player p);





