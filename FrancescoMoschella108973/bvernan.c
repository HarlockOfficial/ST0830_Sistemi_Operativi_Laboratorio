#include "utilities.h"
#include "bvernan_data.h"
#include "bvernan.h"
#include "byte_type.h"


int apply_encryption(data d);

//int apply_encryption_alt(data d);

int read_and_encrypt_byte(data d);

int apply_vernam(const char *key_filename, const char *input_filename, const char *output_filename) {
    data d;
    if (initialize_data(key_filename, input_filename, output_filename, &d) != 0) {
        return 1;
    }
    if (apply_encryption(d) != 0) {
        return 1;
    }
    clean_data(&d);
    return 0;
}

int apply_encryption(const data d) {
    long block_count = (d.input_length / d.block_length) +
                       (d.input_length % d.block_length == 0 ? 0 : 1);
    int ret = 0;
    for (long block_index = 0; block_index < block_count; ++block_index) {
        fseek(d.key, block_index % d.block_length, SEEK_SET);
        for (long byte_index = 0; byte_index < d.block_length; ++byte_index) {
            if ((ret = read_and_encrypt_byte(d)) != 0) {
                break;
            }
        }
    }
    return ret <= 0 ? 0 : ret;
}

/*
//feof is slower then for i in block count
int apply_encryption_alt(const data d){
    int ret = 0, block_index=0;
    while(!feof(d.input)){
        fseek(d.key, block_index%d.block_length, SEEK_SET);
        for (long byte_index = 0; byte_index < d.block_length; ++byte_index) {
            if ((ret = read_and_encrypt_byte(d)) != 0) {
                break;
            }
        }
        ++block_index;
    }
    return ret<=0?0:ret;
}
*/
int read_and_encrypt_byte(const data d) {
    byte _d, _b, _d1;
    int ret = read_next_byte(&_d, d.input);
    if (ret != 0) {
        return ret;
    }
    ret = read_next_byte(&_b, d.key);
    if (ret == -1) {
        //key eof
        fseek(d.key, 0, SEEK_SET);
        ret = read_next_byte(&_b, d.key);
    }
    if (ret != 0) {
        return ret;
    }
    _d1 = _b ^ _d;
    fwrite(&_d1, sizeof(byte), 1, d.output);
    if (file_error_check(d.output) != 0) {
        return 1;
    }
    return 0;
}