#include "crypto.h"

#include <string.h>

int initialize_header(FileCryptHeader *header) {
    header->version = FILECRYPT_VERSION;
    memcpy(header->magic, FILECRYPT_MAGIC, 4);
    randombytes_buf(header->salt, sizeof(header->salt));

    return 1;
}

int derive_key(unsigned char *key, const char *password, const unsigned char *salt) {
    int derived_key = crypto_pwhash(
        key, 
        crypto_secretstream_xchacha20poly1305_KEYBYTES, 
        password, 
        strlen(password), 
        salt, 
        crypto_pwhash_OPSLIMIT_INTERACTIVE, 
        crypto_pwhash_MEMLIMIT_INTERACTIVE, 
        crypto_pwhash_ALG_DEFAULT
    );

    if (derived_key == 0) {
        return 1;
    }
    return 0;
}

int initialize_encryption(
    crypto_secretstream_xchacha20poly1305_state *state, 
    FileCryptHeader *header, 
    const unsigned char *key
) {
    if (crypto_secretstream_xchacha20poly1305_init_push(state, header->stream_header, key) == 0) {
        return 1;
    }
    return 0;
}