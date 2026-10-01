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

#endif