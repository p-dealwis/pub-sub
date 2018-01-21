# PUB-SUB Summer Project

## Dev Libraries Used
[linker = args]
libgcrypt20-dev - Libgcrypt = `libgcrypt-config --libs`
libssl-dev - OpenSSL = -lssl -lcrypto
libsodium-dev - LibSodium  (Generating random seed numbers and keys) = -lsodium

##KP-ABE Library Dependencies
gmp - The GNU Multiple Precision Arithmetic Library - https://gmplib.org/
pbc - Pairing-Based Cryptography Library - https://crypto.stanford.edu/pbc/
---> Installed in /usr/local/ folder so will need to give header paths to compiler
mbedcrypto from mbedtls
(for the tests only) Boost.Test - libboost-all-dev