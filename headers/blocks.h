#include<stdio.h>

#include "infoBlock.h"
#include "infoBag.h"

Block * drawBlocks(Game *g);
void createBag(Game *g);
void decrementFromBag(Game *g);

void deleteBlocksControl(Game *g);
short verifyPlayerHand(Player p, Block b);
void removeBlockFromHand(Player *players, short player_number, Block b);
void completeBlocksNumber(Game *g, Player *players, short player_number);
Block drawOneBlock(Game *g);
void changeBlock(Game *g, Player *players, short player_number, Block b);
