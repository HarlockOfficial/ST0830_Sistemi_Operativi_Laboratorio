#include <stdio.h>
#include <stdlib.h>

#include "input.h"
#include "caesar.h"

//TODO fix problem due to string length ex "0123456789abcdefghijklmnopq" too long!

int main() {
    char *input_string = (char*) malloc(sizeof(char));
    if(input_string==NULL){
        printf("Error making string, no space left");
        return 0;
    }
    long long int len = input(input_string);
    if(len == 0){
        exit(-1);
    }
    encrypt(input_string, len);
    printf("Encrypted: %s", input_string);
    decrypt(input_string, len);
    printf("Decrypted: %s", input_string);
    free(input_string);
    return 0;
}
