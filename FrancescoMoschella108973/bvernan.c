#include <stdio.h>
#include "bvernan.h"

typedef struct data_t {
    FILE *input, *output, *key;
    long block_length, input_length;
}data;

int apply(data *d);
int transform(data *d, int shift);
int initialize_data(char *key_filename, char *input_filename, char *output_filename, data* d);
void clean_data(data* d);

int apply_vernam(char *key_filename, char *input_filename, char *output_filename){
    data d;
    if(initialize_data(key_filename, input_filename, output_filename, &d)!=0){
        return 1;
    }
    if(apply(&d)!=0){
        return 1;
    }
    clean_data(&d);
    return 0;
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

int apply(data* d){
    long block_count = (d->input_length / d->block_length) +
                       (d->input_length % d->block_length == 0 ? 0 : 1);
    int ret;
    for(int i=0; i < block_count; ++i){
        if((ret = transform(d, i))!=0){
            break;
        }
    }
    return ret;
}

int transform(data *d, int shift) {
    fseek(d->key, shift%(d->block_length), SEEK_SET);
    int ret = 0;
    for(int i=0;i<d->block_length;++i){
        byte _d,_b,_d1;
        if((ret = read_byte(&_d, d->input))!=0){
            break;
        }
        if((ret = read_byte(&_b, d->key))!=0){
            break;
        }
        if(feof(d->key)){
            fseek(d->key, 0, SEEK_SET);
        }
        if(feof(d->input)){
            break;
        }
        _d1 = _b ^ _d;
        fwrite(&_d1, sizeof(byte), 1, d->output);
        if((ret=file_error_check(d->output))!=0){
            break;
        }
    }
    return ret;
}

int initialize_data(char *key_filename, char *input_filename, char *output_filename, data *d){
    d->key = fopen(key_filename, "rb");
    d->input = fopen(input_filename, "rb");
    d->output = fopen(output_filename, "wb");
    d->block_length = get_file_length(d->key);
    d->input_length = get_file_length(d->input);
    return d->key == NULL || d->input == NULL || d->output == NULL || d->block_length<=0 || d->input_length <= 0;
}

void clean_data(data *d){
    fclose(d->key);
    fclose(d->input);
    fclose(d->output);
    d->key = NULL;
    d->input = NULL;
    d->output = NULL;
    d->block_length = 0;
    d->input_length = 0;
}
