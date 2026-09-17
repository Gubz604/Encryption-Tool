#include <stdio.h>
#include <string.h>

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

    printf("Successfully opened: %s\n", argv[2]);

    unsigned char buffer[1024];
    size_t total_bytes = 0;
    
    while (1) {
        size_t bytes_read = fread(buffer, 1, sizeof(buffer), file);

        if (bytes_read > 0) {
            printf("Read: %zu bytes\n", bytes_read);
            total_bytes += bytes_read;
        }

        if (bytes_read < sizeof(buffer)) {
            if (ferror(file)) {
                fprintf(stderr, "Error during reading occurred\n");
                fclose(file);
                return 1;
            }

            if (feof(file)) {
                printf("End of file reached\n");
                break;
            }
        }
    }

    printf("Total bytes read: %zu\n", total_bytes);

    fclose(file);
    return 0;
}