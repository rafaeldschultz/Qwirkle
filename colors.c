#include<stdio.h>

void reset(){
    printf("\e[0m");
}

void black(short mode){
    switch (mode){
        case 0: printf("\e[0;30m");         //Regular
            break;
        case 1: printf("\e[1;30m");         //Bold
            break;
        case 2: printf("\e[4;30m");         //Underline
            break;
        case 3: printf("\e[40m");           //Background
            break;
        case 4: printf("\e[0;90m");         //High Intensity
            break;
        case 5: printf("\e[1;90m");         //Bold Hight Intensity
            break;
        case 6: printf("\e[0;100m");        //High Intensity Background
            break;
    }
}

void red(short mode){
    switch (mode){
        case 0: printf("\e[0;31m");         //Regular
            break;
        case 1: printf("\e[1;31m");         //Bold
            break;
        case 2: printf("\e[4;31m");         //Underline
            break;
        case 3: printf("\e[41m");           //Background
            break;
        case 4: printf("\e[0;91m");         //High Intensity
            break;
        case 5: printf("\e[1;91m");         //Bold Hight Intensity
            break;
        case 6: printf("\e[0;101m");        //High Intensity Background
            break;
    }
}

void green(short mode){
    switch (mode){
        case 0: printf("\e[0;32m");         //Regular
            break;
        case 1: printf("\e[1;32m");         //Bold
            break;
        case 2: printf("\e[4;32m");         //Underline
            break;
        case 3: printf("\e[42m");           //Background
            break;
        case 4: printf("\e[0;92m");         //High Intensity
            break;
        case 5: printf("\e[1;92m");         //Bold Hight Intensity
            break;
        case 6: printf("\e[0;102m");        //High Intensity Background
            break;
    }
}

void yellow(short mode){
    switch (mode){
        case 0: printf("\e[0;33m");         //Regular
            break;
        case 1: printf("\e[1;33m");         //Bold
            break;
        case 2: printf("\e[4;33m");         //Underline
            break;
        case 3: printf("\e[43m");           //Background
            break;
        case 4: printf("\e[0;93m");         //High Intensity
            break;
        case 5: printf("\e[1;93m");         //Bold Hight Intensity
            break;
        case 6: printf("\e[0;103m");        //High Intensity Background
            break;
    }
}

void blue(short mode){
    switch (mode){
        case 0: printf("\e[0;34m");         //Regular
            break;
        case 1: printf("\e[1;34m");         //Bold
            break;
        case 2: printf("\e[4;34m");         //Underline
            break;
        case 3: printf("\e[44m");           //Background
            break;
        case 4: printf("\e[0;94m");         //High Intensity
            break;
        case 5: printf("\e[1;94m");         //Bold Hight Intensity
            break;
        case 6: printf("\e[0;104m");        //High Intensity Background
            break;
    }
}

void purple(short mode){
    switch (mode){
        case 0: printf("\e[0;35m");         //Regular
            break;
        case 1: printf("\e[1;35m");         //Bold
            break;
        case 2: printf("\e[4;35m");         //Underline
            break;
        case 3: printf("\e[45m");           //Background
            break;
        case 4: printf("\e[0;95m");         //High Intensity
            break;
        case 5: printf("\e[1;95m");         //Bold Hight Intensity
            break;
        case 6: printf("\e[0;105m");        //High Intensity Background
            break;
    }
}

void cyan(short mode){
    switch (mode){
        case 0: printf("\e[0;36m");         //Regular
            break;
        case 1: printf("\e[1;36m");         //Bold
            break;
        case 2: printf("\e[4;36m");         //Underline
            break;
        case 3: printf("\e[46m");           //Background
            break;
        case 4: printf("\e[0;96m");         //High Intensity
            break;
        case 5: printf("\e[1;96m");         //Bold Hight Intensity
            break;
        case 6: printf("\e[0;106m");        //High Intensity Background
            break;
    }
}

void white(short mode){
    switch (mode){
        case 0: printf("\e[0;37m");         //Regular
            break;
        case 1: printf("\e[1;37m");         //Bold
            break;
        case 2: printf("\e[4;37m");         //Underline
            break;
        case 3: printf("\e[47m");           //Background
            break;
        case 4: printf("\e[0;97m");         //High Intensity
            break;
        case 5: printf("\e[1;97m");         //Bold Hight Intensity
            break;
        case 6: printf("\e[0;107m");        //High Intensity Background
            break;
    }
}