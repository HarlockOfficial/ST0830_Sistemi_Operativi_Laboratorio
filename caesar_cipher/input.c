#include <stdio.h>
#include <stdlib.h>

#include "input.h"

long long int input(char *arr){
    long long int i = 0;
    while(1) {
        int ch=getc(stdin);
        if(ch==EOF){
            arr[i]=0;
            break;
        }
        if((char)ch=='\b' && i>0){
            arr = (char*)realloc(arr, sizeof(arr[0])*(i--));
            //cannot fail, previously incremented
            continue;
        }
        arr[i++] = (char)ch;
        arr = (char*)realloc(arr, sizeof(arr[0])*(i+1));
        if(arr==NULL){
            printf("Error editing string, no space left");
            return 0;
        }
        if((char)ch=='\n') {
            arr[i]=0;
            break;
        }
    }
    return i;
}