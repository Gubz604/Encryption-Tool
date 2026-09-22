#include <stdio.h>
#include <string.h>

int copy_file_data(FILE *input, FILE *output);

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Error: incorrect number of arguments\nUsage: ./filecrypt <command> <filename>\n");
        return 1;
    }

    if (strcmp(argv[1], "encrypt") != 0 && 
        strcmp(argv[1], "decrypt") != 0) {
        fprintf(stderr, "Error: unknown command '%s'\nUsage: ./filecrypt <command> <filename>\n", argv[1]);
        return 1;
    }

    printf("Command: %s\nFile: %s\n", argv[1], argv[2]);

    FILE *file = fopen(argv[2], "rb");

    if (file == NULL) {
        fprintf(stderr, "Error: failed to open file: %s\n", argv[2]);
        
        return 1;
    }

    FILE *output;

    if (strcmp(argv[1], "encrypt") == 0) {
        size_t filename_length = strlen(argv[2]);
        size_t extension_length = strlen(".enc");

        char output_name[
            filename_length +
            extension_length +
            1
        ];

        strcpy(output_name, argv[2]);
        strcat(output_name, ".enc");

        output = fopen(output_name, "wb");

        printf("Input: %s\nOutput: %s\n", argv[2], output_name);
    } else {
        output = fopen("output", "wb");
    }

    if (output == NULL) {
        fprintf(stderr, "Error: failed to open output file\n");

        fclose(file);
        return 1;
    }

    printf("Successfully opened: %s\n", argv[2]);

    int copy_success = copy_file_data(file, output);

    fclose(file);
    fclose(output);

    if (!copy_success) {
        fprintf(stderr, "Error copying data from input to output\n");
        return 1;
    }
    return 0;
}

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