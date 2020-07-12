#include<stdio.h>

#include "infoBlock.h"

Block * drawBlocks(Game *g);
short ** createBlocksControl();
void deleteBlocksControl(Game *g);
short verifyPlayerHand(Player p, Block b);
