#include<stdio.h>

#include "infoBlock.h"
#include "infoBag.h"

/******************
 * BAG WITH TILES *
 ******************/
void createBag(Game *g);
void deleteBlocksControl(Game *g);
void incrementBag(Game *g);
void decrementFromBag(Game *g);

/****************
 * VERIFICACOES *
 ****************/
short verifyBlock(Game *g, Block b);
short verifyPlayerHand(Player p, Block b);

/***********
 * SORTEIO *
 ***********/
Block drawOneBlock(Game *g);
Block * drawBlocks(Game *g);
void completeBlocksNumber(Game *g, Player *p);

/********************************
 * ALTERAR BLOCOS DE UM JOGADOR *
 ********************************/
void removeBlockFromHand(Player *p, Block b);
void changeBlock(Game *g, Player *p, Block b);
