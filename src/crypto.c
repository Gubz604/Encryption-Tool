#include "crypto.h"

#include <string.h>

int initialize_header(FileCryptHeader *header) {
    header->version = FILECRYPT_VERSION;
    memcpy(header->magic, FILECRYPT_MAGIC, 4);
    randombytes_buf(header->salt, sizeof(header->salt));

    return 1;
}