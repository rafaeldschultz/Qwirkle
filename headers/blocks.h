#include<stdio.h>

#include "infoBlock.h"

Block * drawBlocks(Game *g);
short ** createBlocksControl();
void deleteBlocksControl(Game *g);
short verifyPlayerHand(Player p, Block b);
void removeBlockFromHand(Player *players, short player_number, Block b);
void completeBlocksNumber(Game *g, Player *players, short player_number);
Block drawOneBlock(Game *g);
void changeBlock(Game *g, Player *players, short player_number, Block b);
