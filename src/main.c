#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Error: incorrect number of arguments\nUsage: ./filecrypt <command> <filename>\n");
        return 1;
    }

    printf("Command: %s\nFile: %s\n", argv[1], argv[2]);

    return 0;
}