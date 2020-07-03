#include<stdio.h>

#include "headers/infoBoard.h"
#include "headers/colors.h"

void showBoard(Board * tafel){
    
    short minCol = (BOARD_DIM/2) - tafel->max_x - 1;
    short minLin = (BOARD_DIM/2) - tafel->max_y - 1;
    short maxCol = (BOARD_DIM/2) + tafel->max_x - 1;
    short maxLin = (BOARD_DIM/2) + tafel->max_y - 1;

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
