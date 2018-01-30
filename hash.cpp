#include <gcrypt.h>

#include "hash.h"
// #include "miracl.h"

#define KEY_SIZE 16
#define SHA256_DIGEST_LENGTH 32
#define TRUE 1
#define FALSE 0

// void uocrypt_error(gcry_error_t err)
// {
//     if (err)
//     {
//         fprintf(stderr, "Failure: %s/%s\n", gcry_strsource(err), gcry_strerror(err));
//         abort();
//     }
// }

void KeyedHash(uint8_t *key, int keyLength, uint8_t *data, int dataLength, uint8_t *mac, int macLength)
{
    gcry_md_hd_t hd;
    // gcry_error_t err = GPG_ERR_NO_ERROR;

    gcry_md_open(&hd, GCRY_MD_SHA256, GCRY_MD_FLAG_HMAC);
    // uocrypt_error(err);

    gcry_md_setkey(hd, key, keyLength); //keyLength must be 32 bytes or less
    // uocrypt_error(err);

    gcry_md_write(hd, data, dataLength);

    uint8_t *p = gcry_md_read(hd, GCRY_MD_SHA256);
    memcpy(mac, p, SHA256_DIGEST_LENGTH);
    gcry_md_close(hd);
}

// void KeyedHash(uint8_t *key, int keyLength, uint8_t *data, int dataLength, uint8_t *mac, int macLength)
// {
//     int i;
//     sha256 md;
//     shs256_init(&md); //The SHA for hashing

//     for(i=0; i<keyLength; i++)
//         shs256_process(&md, key[i]);

//     for(i=0; i<dataLength; i++)
//         shs256_process(&md, data[i]);

//     shs256_hash(&md, (char*)mac);
//     mac[SHA256_DIGEST_LENGTH]=0;
// }

int permutation(int seed, bool *array, int len)
{
    srand(seed);
    size_t j;

    if (len > 1)
    {
        size_t i;
        for (i = len - 1; i > 0; i--)
        {
            j = (unsigned int)rand() % i;
            bool t = array[j];
            array[j] = array[i];
            array[i] = t;
        }
    }

    return seed;
}
