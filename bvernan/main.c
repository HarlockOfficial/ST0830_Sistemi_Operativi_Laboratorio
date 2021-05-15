#include <stdio.h>
#include "bvernan.h"

int main(int argc, char **argv) {
    if(argc!=4){
        printf("Usage %s <key_filename> <input_filename> <output_filename>\n", argv[0]);
        return 1;
    }
    int res = apply_vernam(argv[1], argv[2], argv[3]);
    if(res!=0){
        perror("Errore durante il lavoro sui file\n");
    }
    return res;
}
