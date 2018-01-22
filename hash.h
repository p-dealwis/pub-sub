#ifndef HASH_H
#define HASH_H

#include <gcrypt.h>
#include <stdint.h>

void uocrypt_error(gcry_error_t err);
void KeyedHash(uint8_t *key, int keyLength, uint8_t *data, int dataLength, uint8_t *mac, int macLength);
int permutation(int seed, bool *array, int len);

#endif