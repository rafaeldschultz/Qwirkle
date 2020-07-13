#include<stdio.h>

/*
 * Limpa o buffer de entrada ate um enter ('\n')
 */
void cleanBufferEnter(){
    char ch;               
    do {
        ch = fgetc(stdin);
    } while (ch != EOF && ch != '\n');
}

/*
 * Limpa o buffer de entrada ate um espaco (' ')
 */
void cleanBufferSpace(){
    char ch;               
    do {
        ch = fgetc(stdin);
    } while (ch != EOF && ch != ' ');
}
