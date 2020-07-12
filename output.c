#include <stdio.h>

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

void showOnePlayerTiles(Player p){
    green(0);
    printf("Pecas: ");
    for(short i = 0; i < 6; i++){
        if(p.tiles[i].letter != '\0'){
            numberToColor(p.tiles[i].number);
            printf("%c%hd ", p.tiles[i].letter, p.tiles[i].number);
        }
    }
    printf("\n");
}

void playerOptions(){
    blue(0);
    printf("Opcoes: \n");

    blue(1);
    printf("\t - jogar");
    reset();
    yellow(1);
    printf(" peca");
    purple(1);
    printf(" linha coluna\n");
    blue(1);
    printf("\t - trocar");
    reset();
    yellow(1);
    printf(" peca\n");
    blue(1);
    printf("\t - passar\n\n");
    blue(1);
    printf("Selecione:   ");
    reset();
}

void showPlayersTiles(Game g, Player *players){
    blue(1);
    printf("\n\t     PEÇAS\n\n");
    
    for(short i = 0; i < g.n_players; i++){
        blue(1);
        printf("- %s:", players[i].name);
        reset();

        for(short j = 0; j < 6; j++){
            if(players[i].tiles[j].letter != '\0'){
                printf(" ");
                numberToColor(players[i].tiles[j].number);
                printf("%c", players[i].tiles[j].letter);
                printf("%hd", players[i].tiles[j].number);
                reset();
            }
        }
        
        printf("\n\n");
    }
}

void showBoard(Game *g){
    //Print título
    green(1);
    printf("\n            ");
    for(short i = 0; i < g->max_col; i++){
        printf("  ");
    }
    printf("TABULEIRO\n\n");
    reset();

    //Printa linha de apoio
    printf("\t     ");
    for(short j = 0; j <= g->max_col; j++){
        printf(" %3hd", j);
    }
    printf("\n\t     ┌");
    for(short j = 0; j <= g->max_col; j++){
        printf("────");
    }
    printf("┐\n");


    //printa o tabuleiro
    for(short i = 0; i <= g->max_lin; i++){
        //printa coluna de apoio
        printf("\t%3hd  │", i);

        for(short j = 0; j <= g->max_col; j++){
            if(g->board[i][j].letter != '\0'){
                numberToColor(g->board[i][j].number);
                printf(" %c%d ", g->board[i][j].letter, g->board[i][j].number);
                reset();
            } else {
                printf("    ");
            }
        }

        //printa coluna de apoio
        printf("│%3hd", i);
        printf("\n");
    }

    //Printa linha de apoio
    
    printf("\t     └");
    for(short j = 0; j <= g->max_col; j++){
        printf("────");
    }
    printf("┘\n\t     ");
    for(short j = 0; j <= g->max_col; j++){
        printf(" %3hd", j);
    }
    printf("\n");
}

void invalidBlock(short a){
    red(1);
    if(a == 0){
        printf("\nPeca inserida invalida!\n\n");
    } else {
        printf("\nVoce nao possui essa peca!\n\n");
    }
    reset();
}

void invalidPosition(){
    red(1);
    printf("\nPosicao Invalida!\n\n");
    reset();
}

void invalidOption(short n){
    red(1);
    if(n == 0) printf("\nOpcao invalida!\n\n");
    else printf("\nVoce pode realizar apenas um tipo de jogada por rodada!\n\n");
    reset();
}

void invalidMove(){
    red(1);
    printf("\nMovimento invalido!\n\n");
    reset();
}

void cheatModeMenu(){
    green(1);
    printf("Cheat Mode (S/N): ");
    reset();
}

void noMoreBlocksBag(){
    yellow(1);
    printf("\nNao ha mais pecas para serem distribuidas!\n\n");
    reset();
}
