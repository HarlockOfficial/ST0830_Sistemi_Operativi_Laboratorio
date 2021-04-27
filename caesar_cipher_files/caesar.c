#include "caesar.h"
#include "constraints.h"

typedef char byte;

void encrypt(char* input, char* output){
    FILE *in = fopen(input, "rb"), *out = fopen(output, "wb");
    if(in==NULL || out==NULL){
        perror("Impossible to open input or output file");
        exit(1);
    }
    byte b;
    unsigned long val;
    while((val = fread(&b, sizeof(b), 1, in)) != 0){
        if(val<0){
            perror("File related error");
            exit(1);
        }
        b += SHIFT - (b+SHIFT>0xFF?0xFF:0);
        fwrite(&b, sizeof(b), 1, out);
    }
    fclose(in);
    fclose(out);
}

void decrypt(char* input, char* output){
    FILE *in = fopen(input, "rb"), *out = fopen(output, "wb");
    if(in==NULL || out==NULL){
        perror("Impossible to open input or output file");
        exit(1);
    }
    byte b;
    unsigned long val;
    while((val = fread(&b, sizeof(b), 1, in)) != 0){
        if(val<0){
            perror("File related error");
            exit(1);
        }
        b -= SHIFT + (b-SHIFT<0?0xFF:0);
        fwrite(&b, sizeof(b), 1, out);
    }
    fclose(in);
    fclose(out);
}