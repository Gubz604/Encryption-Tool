#include "file_io.h"

int copy_file_data(FILE *input, FILE *output) {
    unsigned char buffer[1024];
    size_t total_bytes = 0;

    while(1) {
        size_t bytes_read = fread(buffer, 1, sizeof(buffer), input);

        if (bytes_read > 0) {
            printf("Read: %zu bytes\n", bytes_read);
            total_bytes += bytes_read;

            size_t output_produced = fwrite(buffer, 1, bytes_read, output);
        
            if (output_produced != bytes_read) {
                fprintf(stderr, "Error: bytes written different than read\nBytes Read: %zu\nBytes written %zu\n", 
                        bytes_read, output_produced);

                return 0;
            }
        }

        if (bytes_read < sizeof(buffer)) {
            if (ferror(input)) {
                fprintf(stderr, "Error during reading occurred\n");

                return 0;
            }

            if (feof(input)) {
                printf("End of file reached\n");
                break;
            }
        }
    }

    printf("Total bytes read: %zu\n", total_bytes);
    return 1;
}