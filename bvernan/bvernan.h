#ifndef BVERNAN_BVERNAN_H
#define BVERNAN_BVERNAN_H
    typedef unsigned char byte;

    int apply_vernam(char *key_filename, char *input_filename, char *output_filename);
    long get_file_length(FILE *fp);
    int file_error_check(FILE *fp);
    int read_byte(byte *b, FILE *fp);
#endif //BVERNAN_BVERNAN_H
