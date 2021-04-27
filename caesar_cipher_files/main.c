#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "caesar.h"

int main(int argc, char **argv) {
    if(argc < 4){
        printf("Usage: %s [encrypt|decrypt] <input filename> <output filename>", argv[0]);
        exit(1);
    }
    if(strcmp(argv[1],"encrypt")==0){
        encrypt(argv[2], argv[3]);
    }else if(strcmp(argv[1], "decrypt")==0){
        decrypt(argv[2], argv[3]);
    }else{
        printf("Usage: %s [encrypt|decrypt] <input filename> <output file name>", argv[0]);
        exit(1);
    }
    return 0;
}
