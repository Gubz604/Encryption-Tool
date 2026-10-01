#ifndef CRYPTO_H
#define CRYPTO_H

#include <stdint.h>
#include <sodium.h>

#define FILECRYPT_MAGIC "FCRY"
#define FILECRYPT_VERSION 1

typedef struct {
    unsigned char magic[4];
    uint8_t version;
    unsigned char salt[crypto_pwhash_SALTBYTES];
    unsigned char stream_header[crypto_secretstream_xchacha20poly1305_HEADERBYTES];
} FileCryptHeader;

int initialize_header(FileCryptHeader *header);

int derive_key(unsigned char *key, const char *password, const unsigned char *salt);

int initialize_encryption(
    crypto_secretstream_xchacha20poly1305_state *state, 
    FileCryptHeader *header, 
    const unsigned char *key
);

int encrypt_chunk(
    crypto_secretstream_xchacha20poly1305_state *state,
    const unsigned char *input,
    size_t input_length,
    unsigned char *output,
    unsigned long long *output_length
);

#endif