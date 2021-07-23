#ifndef FRANCESCOMOSCHELLA108973_UTILITIES_H
#define FRANCESCOMOSCHELLA108973_UTILITIES_H
#include "byte_type.h"
#include <stdio.h>

long get_file_length(FILE *fp);

int file_error_check(FILE *fp);

int read_next_byte(byte* b, FILE *fp);
#endif
