#ifndef FRANCESCOMOSCHELLA108973_BVERNAN_DATA_H
#define FRANCESCOMOSCHELLA108973_BVERNAN_DATA_H

#include <stdio.h>

typedef struct data_t {
    FILE *input, *output, *key;
    long block_length, input_length;
} data;

int initialize_data(const char *key_filename, const char *input_filename, const char *output_filename, data *d);

void clean_data(data *d);

#endif
