#include <stdio.h>
#include <stdlib.h>

#include "input.h"

long long int input(char **arr){
    long long int i = 0;
    while(1) {
        int ch=getc(stdin);
        if(ch==EOF || ch==(int)'\n') {
            break;
        }
        (*arr)[i++] = (char)ch;
        (*arr) = (char*)realloc(*arr, sizeof(char)*(i+1));
        if((*arr)==NULL){
            free(*arr);
            perror("Error editing string, no space left\n");
            return -1;
        }
    }
    (*arr)[i]=0;
    return i;
}