#include "utilities.h"


long get_file_length(FILE *fp) {
    fseek(fp, 0, SEEK_END);
    long length = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    return length;
}

int file_error_check(FILE *fp) {
    if (ferror(fp)) {
        perror("Error during file operation, quitting");
        return 1;
    }
    return 0;
}

int read_next_byte(byte *b, FILE *fp) {
    size_t read_byte_quantity = fread(b, sizeof(unsigned char), 1, fp);
    if(read_byte_quantity==0){
        return -1;
    }
    return file_error_check(fp);
}