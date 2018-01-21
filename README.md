# PUB-SUB Summer Project

## Dev Libraries Used
[linker = args]
libgcrypt20-dev - Libgcrypt = `libgcrypt-config --libs`
libssl-dev - OpenSSL = -lssl -lcrypto
libsodium-dev - LibSodium  (Generating random seed numbers and keys) = -lsodium

##KP-ABE Library Dependencies
kpabe-yct14-cpp - https://github.com/ikalchev/kpabe-yct14-cpp.git = -lkpabe
GMP - The GNU Multiple Precision Arithmetic Library - https://gmplib.org/ = -lpbc 
PBC - Pairing-Based Cryptography Library - https://crypto.stanford.edu/pbc/ = -lm -lgmp 
---> Installed in /usr/local/ folder
mbedcrypto from mbedtls - libmbedtls-dev = -lmbedcrypto
(for the tests only) Boost.Test - libboost-all-dev

Include /usr/local/lib = -L. -L/usr/local/lib

To generate test script for the KP-ABE library:
g++ -o kpabe_test kpabe_test.o -L. -L/usr/local/lib -lm -lkpabe -lboost_unit_test_framework -lpbc -lgmp -lmbedcrypto
