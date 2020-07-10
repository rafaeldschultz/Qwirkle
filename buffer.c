#include<stdio.h>

void cleanBufferEnter(){
    char ch;               
    do {
        ch = fgetc(stdin);
    } while (ch != EOF && ch != '\n');
}

void cleanBufferSpace(){
    char ch;               
    do {
        ch = fgetc(stdin);
    } while (ch != EOF && ch != ' ');
}
