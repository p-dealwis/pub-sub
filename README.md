# PUB-SUB Summer Project



```
g++ -std=gnu++14 -o main.exe main.cpp Tag.cpp hash.cpp pub_sub.cpp Gate.cpp kpabe.cpp -I. -I/usr/local/include -I/usr/local/include/pbc `libgcrypt-config --libs` -lcrypto -lsodium -lpbc -lgmp -lmbedcrypto -lm
```

## Dev Libraries Used
[linker = args]
libgcrypt20-dev - Libgcrypt = `libgcrypt-config --libs`
libssl-dev - OpenSSL = -lssl -lcrypto
libsodium-dev - LibSodium  (Generating random seed numbers and keys) = -lsodium

##KP-ABE Library Dependencies
kpabe-yct14-cpp - https://github.com/ikalchev/kpabe-yct14-cpp.git = -lkpabe
GMP - The GNU Multiple Precision Arithmetic Library - https://gmplib.org/ = -lpbc 
PBC - Pairing-Based Cryptography Library - https://crypto.stanford.edu/pbc/ = -lgmp 
---> Installed in /usr/local/ folder
mbedcrypto from mbedtls - libmbedtls-dev = -lmbedcrypto -lm
(for the tests only) Boost.Test - libboost-all-dev

Include /usr/local/lib = -I. -I/usr/local/include -I/usr/local/include/pbc

To generate test script for the KP-ABE library:
g++ -o kpabe_test kpabe_test.o -L. -L/usr/local/lib -lm -lkpabe -lboost_unit_test_framework -lpbc -lgmp -lmbedcrypto
