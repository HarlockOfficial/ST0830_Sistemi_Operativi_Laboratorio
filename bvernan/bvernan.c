#include <stdio.h>
#include "bvernan.h"

int apply(FILE *key_file, FILE *input_file, FILE *output_file);
int transform(FILE *key_file, FILE *input_file, FILE *output_file, int shift, long block_length);

int apply_vernam(char *key_filename, char *input_filename, char *output_filename){
    FILE *key, *input, *output;
    int ret;
    key = fopen(key_filename, "rb");
    if (key == NULL) {
        ret = 1;
    } else {
        input = fopen(input_filename, "rb");
        if (input == NULL) {
            ret = 1;
            fclose(key);
        } else {
            output = fopen(output_filename, "wb");
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
    long key_length = get_file_length(key_file);
    long input_length = get_file_length(input_file);
    if(key_length==0){
        return 1;
    }
    long block_count = (input_length / key_length) + (input_length % key_length == 0 ? 0 : 1);
    int ret;
    for(int i=0; i < block_count; ++i){
        ret = transform(key_file, input_file, output_file, i, key_length);
        if(ret != 0){
            break;
        }
    }
    return ret;
}

int transform(FILE *key_file, FILE *input_file, FILE *output_file, int shift, long block_length) {
    fseek(key_file, shift%block_length, SEEK_SET);
    int ret = 0;
    for(int i=0;i<block_length;++i){
        byte d,b,d1;
        if(feof(key_file)){
            fseek(key_file, 0, SEEK_SET);
        }
        if(feof(input_file)){
            break;
        }
        if((ret = read_byte(&d, input_file))!=0){
            break;
        }
        if((ret = read_byte(&b, key_file))!=0){
            break;
        }
        d1 = b ^ d;
        fwrite(&d1, sizeof(byte), 1, output_file);
        if((ret=file_error_check(output_file))!=0){
            break;
        }
    }
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

int read_byte(byte *b, FILE *fp){
    fread(b, sizeof(byte), 1, fp);
    return file_error_check(fp);
}