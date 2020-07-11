#include<stdio.h>
#include<stdlib.h>

#include "headers/infoBlock.h"
#include "headers/infoGame.h"
#include "headers/infoPlayer.h"

#include "headers/colors.h"
#include "headers/output.h"
#include "headers/buffer.h"

int makeMoviment(Game *g, Block b, int lin, int col){
    g->board[lin][col] = b;

    Block empty;
    empty.letter = '\0';
    empty.number = 0;

    if(lin == g->max_lin){
        g->max_lin++;
        g->board = (Block **) realloc(g->board, (g->max_lin + 1) * sizeof(Block *));
        g->board[g->max_lin] = (Block *) calloc(g->max_col, sizeof(Block));
    }

    if(lin == 0){
        g->max_lin++;
        g->board = (Block **) realloc(g->board, (g->max_lin + 1) * sizeof(Block *));
        g->board[g->max_lin] = (Block *) calloc(g->max_col, sizeof(Block));

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

int playerTurn(Game *g, Player p){
    printf("───────────────────────────\n\n");
    blue(1);
    printf("JOGADA DE @%s\n\n", p.name);
    
    showOnePlayerTiles(p);

    blue(1);
    printf("Selecione:   ");

    Block b;
    
    b.letter = fgetc(stdin);
    scanf(" %hd", &b.number);

    int lin, col;
    scanf("%d %d", &lin, &col);

    cleanBufferEnter();
    
    makeMoviment(g, b, lin, col);
    showBoard(g);
}

void gameRounds(Game *g, Player *p){
    short result = 0;

    int i = 0;
    while(!result){
        playerTurn(g, p[i]);
        i = (++i) % (g->n_players);
    }
}
