#include "constraints.h"
#include "caesar.h"

void encrypt(char *arr, long long int len){
    for(long long int i=0;i<len;++i){
        if(arr[i] >= 'a' && arr[i] <= 'z') {
            arr[i] = (char)(((int)'a') + (((((int)arr[i]) - ((int)'a')) + SHIFT) % 26));
        }else if(arr[i] >= 'A' && arr[i] <= 'Z'){
            arr[i] = (char)(((int)'A') + (((((int)arr[i]) - ((int)'A')) + SHIFT) % 26));
        }
    }
}

void decrypt(char *arr, long long int len){
    int tmp;
    for(long long int i=0;i<len;++i){
        if(arr[i] >= 'a' && arr[i] <= 'z') {
            tmp = (((int)arr[i]) - ((int)'a')) - SHIFT;
            arr[i] = (char)((tmp<0?'z':'a')+tmp);
        }else if(arr[i] >= 'A' && arr[i] <= 'Z'){
            tmp = (((int)arr[i]) - ((int)'A')) - SHIFT;
            arr[i] = (char)((tmp<0?'Z':'A')+tmp);
        }
    }
}