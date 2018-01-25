using namespace std;

#include "test.hpp"

#include <gcrypt.h>
#include <sodium.h>
#include <iostream>
#include <time.h>

#include "pbc.h"
#include "Gate.h"
#include "Tag.h"
#include "pub_sub.h"
#include "kpabe.hpp"
#include "Timer.hpp"

vector<Timer> test(string text, int testSize)
{
    vector<Timer> times = {};
    // Initialise GCRYPT
    if (!gcry_check_version(GCRYPT_VERSION))
    {
        fputs("libgcrypt version mismatch\n", stderr);
        exit(2);
    }

    /* A 256 bit key */
    uint8_t *betaKey = (unsigned char *)"01234567890123456789012345678901";

    vector<int> attributeUniverse{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    vector<Tag> pubArray = {};
    vector<Tag> subArray = {};
    
    createTagArray("data.txt", 10, pubArray, subArray);

    //Subscriber Tree
    Gate AND1(Gate::Type::AND, 1, false, 2, false);
    Gate OR1(Gate::Type::OR, &AND1, 0, true);
    Gate OR3(Gate::Type::OR, 3, false, 4, false);
    Gate AND2(Gate::Type::AND, &OR1, &OR3);

    AND2.makeParent();

    //KP-ABE
    PrivateParams priv;
    PublicParams pub;
    setup(attributeUniverse, pub, priv);

    //Make access policy from subscriber tree and generate key
    Node root = AND2.createABETree();
    auto key = keyGeneration(priv, root);

    addTime("Init", clock(), times);

    // Create an attribute-based secret (attributes 1 and 3).
    element_s secret;
    vector<int> encryptionAttributes{0, 1, 2, 3, 4};
    auto Cw = createSecret(pub, encryptionAttributes, secret);

    //Encrypt the message
    std::vector<uint8_t> ciphertext = encrypt(pub, encryptionAttributes, text, Cw);
    addTime("Encrypt of Payload by Pub", clock(), times);

    //Encryption of Interests
    genHashArray(betaKey, subArray);
    addTime("Encrypt Of Filter", clock(), times);

    //Generate r permutation and send to B2
    if (sodium_init() == -1)
    {
        printf("Sodium Library failed to initilise");
    }
    int r = randombytes_random();

    //From Sub to B1 - PRP
    interestPermutation(r, subArray, false);
    addTime("Permutation Time on Sub", clock(), times);

    //Encryption time of Tags
    genHashArray(betaKey, pubArray);
    addTime("Encrypt Of Tags", clock(), times);

    //Done by B1 - Search
    matchInterests(pubArray, subArray);
    addTime("Search time of B1", clock(), times);

    //Done by B2 - PRP Reverse
    interestPermutation(r, subArray, true);
    addTime("PRP reverse B2", clock(), times);

    //Send to B3 - Structure

    //Done by B3 - Evaluation of Tree
    int eval = AND2.evaluate(subArray);
    if (eval == 1) ;//cout << "Evaluated" << endl;
    else cout << "Evaluation Failiure" << endl;
    
    addTime("Evaluation of tree by B3", clock(), times);
    
    //Decryption of payload
    vector<int> testAttributes{1, 2, 4};
    string result;
    try
    {
        result = decrypt(key, Cw, testAttributes, ciphertext);
    }
    catch (const UnsatError &e)
    {
        cout << "Decryption Error" << endl;
    }
    addTime("Decryption of Payload by sub", clock(), times);
    totalTime(times, false);
    totalTime(times);
    if (result == text) ;//cout << "Decrypted Successfully" << endl;
    else cout << "Unsuccessful Decryption" << endl;
    return times;
}

static const char alphanum[] = "0123456789!@#$^&*ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz ";

string randomString(int len){
    srand (time(NULL));
    string text = "";
    for(int i = 0; i < len; i++){
        int num = rand() % 70;
        text += alphanum[num];
    }
    return text;
}