# PUB-SUB Summer Project

### To run:
`./main.out <testCases No.> <Number of tests per run (default 100)> <output filename (default results.txt)>`

Test Cases:
1. 1KB -> 16MB
2. 32MB -> 64MB
3. 128MB
4. 1KB -> 128MB

### To complie:

```
g++ -std=gnu++14 -o main.out main.cpp test.cpp Timer.cpp Tag.cpp hash.cpp pub_sub.cpp Gate.cpp kpabe.cpp -I. -I/usr/local/include -I/usr/local/include/pbc `libgcrypt-config --libs` -lcrypto -lsodium -lpbc -lgmp -lmbedcrypto -lm
```

## Dev Libraries Used
[linker = args]

1. **Libgcrypt** - libgcrypt20-dev = `libgcrypt-config --libs`
2. **OpenSSL** - libssl-dev = `-lssl -lcrypto`
3. **LibSodium** - libsodium-dev (Generating random seed numbers and keys) = `-lsodium`

## KP-ABE Library Dependencies
1. **kpabe-yct14-cpp** - https://github.com/ikalchev/kpabe-yct14-cpp.git = `-lkpabe`
2. **GMP** - The GNU Multiple Precision Arithmetic Library - https://gmplib.org/ = `-lpbc`
3. **PBC** - Pairing-Based Cryptography Library - https://crypto.stanford.edu/pbc/ = `-lgmp` 
    - Installed in /usr/local/ folder
4. **mbedcrypto** from mbedtls - libmbedtls-dev = `-lmbedcrypto -lm`

- Include /usr/local/lib = -I. -I/usr/local/include -I/usr/local/include/pbc
