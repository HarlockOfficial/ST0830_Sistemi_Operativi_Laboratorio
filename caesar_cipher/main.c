#include <stdio.h>
#include <stdlib.h>

#include "input.h"
#include "caesar.h"


int main() {
    char *input_string = (char*) malloc(sizeof(char));
    if(input_string==NULL){
        perror("Error making string, no space left\n");
        return 0;
    }
    long long int len = input(&input_string);
    if(len <= 0){
        if(len==0) {
            perror("Empty String\n");
        }
        exit(1);
    }
    encrypt(input_string, len);
    printf("Encrypted: %s\n", input_string);
    decrypt(input_string, len);
    printf( "Decrypted: %s\n", input_string);
    free(input_string);
    return 0;
}
