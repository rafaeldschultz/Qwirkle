#include<stdio.h>

#include "headers/infoGame.h"
#include "headers/infoPlayer.h"

#include "headers/colors.h"

void numberToColor(short n){
    switch (n){
        case 1: blue(5);
            break;
        case 2: yellow(5);
            break;
        case 3: red(5);
            break;
        case 4: green(5);
            break;
        case 5: purple(5);
            break;
        case 6: cyan(5);
            break;
    }
}

void welcome(){
    red(1);
    printf("\n\t    Q");
    yellow(1);
    printf("W");
    green(1);
    printf("I");
    blue(1);
    printf("R");
    purple(1);
    printf("K");
    cyan(1);
    printf("L");
    red(1);
    printf("E");
    yellow(1);
    printf("!");
    green(1);
    printf("!\n\n");
    reset();
}

void showPlayersTiles(Game g, Player *players){
    blue(1);
    printf("\n\t    PEÇAS\n\n");
    
    for(short i = 0; i < g.n_players; i++){
        blue(1);
        printf("- %s:", players[i].name);
        reset();

        for(short j = 0; j < 6; j++){
            printf(" ");
            numberToColor(players[i].tiles[j].number);
            printf("%c", players[i].tiles[j].letter);
            printf("%hd", players[i].tiles[j].number);
            reset();
        }
        
        printf("\n\n");
    }
}

void showBoard(Game *g){
    //Print título
    blue(1);
    printf("\n\t   TABULEIRO\n\n");
    reset();

    //Printa linha de apoio
    printf("\t    ");
    blue(5);
    for(short j = 0; j <= g->max_col; j++){
        printf(" %+3hd ", (j - g->max_col));
    }
    reset();
    printf("\n");


    //printa o tabuleiro
    for(short i = 0; i <= g->max_lin; i++){
        for(short j = 0; j <= g->max_col; j++){
            //printa coluna de apoio
            blue(5);
            printf("\t%+3hd |", (i - g->max_lin));
            reset();

            for(short j = 0; j <= g->max_lin; j++){
                if(g->board[i][j].letter != '\0'){
                    printf(" %c%d  ", g->board[i][j].letter, g->board[i][j].number);
                } else {
                    printf("     ");
                }
            }

            //printa coluna de apoio
            blue(5);
            printf("| %+3hd", (i - g->max_lin));
            reset();
            printf("\n");
        }
    }

    //Printa linha de apoio
    printf("\t    ");
    blue(5);
    for(short j = 0; j <= g->max_col; j++){
        printf(" %+3hd ", (j - g->max_col));
    }
    reset();
    printf("\n");
}

/*
void showBoard(Game * g){
    
    short minCol = (BOARD_DIM/2) - g->max_x - 1;
    short minLin = (BOARD_DIM/2) - g->max_y - 1;
    short maxCol = (BOARD_DIM/2) + g->max_x - 1;
    short maxLin = (BOARD_DIM/2) + g->max_y - 1;

    short semi_dif_Lin = (maxLin - minLin)/2;
    short semi_dif_Col = (maxCol - minCol)/2;

    //Print título
    blue(1);
    printf("\n\t   TABULEIRO\n\n");
    reset();
    
    //Printa linha de apoio
    printf("\t    ");
    blue(5);
    for(short j = minLin; j <= maxCol; j++){
        printf(" %+3hd ", (j - maxCol) + semi_dif_Col);
    }
    reset();
    printf("\n");
    
    //printa o tabuleiro
    for(short i = minCol; i <= maxCol; i++){
        //printa coluna de apoio
        blue(5);
        printf("\t%+3hd |", (i - maxLin) + semi_dif_Lin);
        reset();

        for(short j = minLin; j <= maxLin; j++){
            if(tafel->tabuleiro[i][j].letter != '\0'){
                printf(" %c%d  ", tafel->tabuleiro[i][j].letter, tafel->tabuleiro[i][j].number);
            } else {
                printf("     ");
            }
        }

        //printa coluna de apoio
        blue(5);
        printf("| %+3hd", (i - maxLin) + semi_dif_Lin);
        reset();

        printf("\n");
    }

    //Printa linha de apoio
    printf("\t    ");
    blue(5);
    for(short j = minLin; j <= maxCol; j++){
        printf(" %+3hd ", (j - maxCol) + semi_dif_Col);
    }
    reset();
    printf("\n");
}
*/
