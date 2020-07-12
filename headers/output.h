#include "infoGame.h"
#include "infoPlayer.h"

/***************
 * Boas-vindas *
 ***************/
void welcome();

/*********************
 * Mensagens de erro *
 *********************/
void invalidNumberPlayers();
void errorAllocation();


void showBoard(Game * g);
void numberToColor(short n);
void showPlayersTiles(Game g, Player *players);
void showOnePlayerTiles(Player p);
void playerOptions();
void invalidBlock(short a);
void invalidPosition();
void invalidOption(short n);
void invalidMove();
void cheatModeMenu();
void noMoreBlocksBag();
