#include "bvernan_data.h"
#include "utilities.h"

int initialize_data(const char *key_filename, const char *input_filename, const char *output_filename, data *d) {
    d->key = fopen(key_filename, "rb");
    d->input = fopen(input_filename, "rb");
    d->output = fopen(output_filename, "wb");
    d->block_length = get_file_length(d->key);
    d->input_length = get_file_length(d->input);
    return d->key == NULL || d->input == NULL || d->output == NULL || d->block_length <= 0 || d->input_length <= 0;
}

void clean_data(data *d) {
    fclose(d->key);
    fclose(d->input);
    fclose(d->output);
    d->key = NULL;
    d->input = NULL;
    d->output = NULL;
    d->block_length = 0;
    d->input_length = 0;
}