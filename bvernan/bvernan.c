#include <stdio.h>
#include <stdlib.h>
#include "bvernan.h"

int apply(FILE *key_file, FILE *input_file, FILE *output_file);
int transform(FILE *key_file, FILE *input_file, FILE *output_file);
long get_file_length(FILE *fp);
int file_error_check(FILE *fp);

typedef unsigned char byte;

int apply_vernam(char *key_filename, char *input_filename, char *output_filename){
    FILE *key, *input, *output;
    int ret;
    key = fopen(key_filename, "r");
    if (key == NULL) {
        ret = 1;
    } else {
        input = fopen(input_filename, "r");
        if (input == NULL) {
            ret = 1;
            fclose(key);
        } else {
            output = fopen(output_filename, "w");
            if (output == NULL) {
                ret = 1;
                fclose(key);
                fclose(input);
            } else {
                ret = apply(key, input, output);
                fclose(key);
                fclose(input);
                fclose(output);
            }
        }
    }
    return ret;
}

int apply(FILE *key_file, FILE *input_file, FILE *output_file){
    long key_length, input_length;
    key_length = get_file_length(key_file);
    input_length = get_file_length(input_file);
    long block_count = (input_length / key_length) + (input_length % key_length == 0 ? 0 : 1);
    int res;
    for(int i=0; i < block_count; ++i){
        res = transform(key_file, input_file, output_file);
        if(res!=0){
            break;
        }
    }
    return res;
}

int transform(FILE *key_file, FILE *input_file, FILE *output_file) {
    int ret = 0;
    while(!feof(key_file)){
        byte d,b,d1;
        if(!feof(input_file)){
            fread(&d, sizeof(byte), 1, input_file);
            if((ret=file_error_check(input_file))!=0){
                break;
            }
        }else{
            d = rand() % 0xff;
        }
        fread(&b, sizeof(byte), 1, key_file);
        if((ret=file_error_check(key_file))!=0){
            break;
        }
        d1 = b ^ d;
        fwrite(&d1, sizeof(byte), 1, output_file);
        if((ret=file_error_check(output_file))!=0){
            break;
        }
    }
    fseek(key_file, 0, SEEK_SET);
    return ret;
}

long get_file_length(FILE *fp){
    fseek(fp, 0, SEEK_END);
    long length = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    return length;
}

int file_error_check(FILE *fp){
    if(ferror(fp)){
        perror("Error during file operation, quitting");
        return 1;
    }
    return 0;
}