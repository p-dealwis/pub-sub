using namespace std;

#include "test.hpp"

#include <gcrypt.h>
#include <sodium.h>
#include <iostream>
#include <time.h>
#include <fstream>
#include <string>
#include <sstream>

#include "pbc.h"
#include "Gate.h"
#include "Tag.h"
#include "pub_sub.h"
#include "kpabe.hpp"
#include "Timer.hpp"

vector<Timer> test(string text, int testSize)
{
    vector<Timer> times = {};
    addTime("Launch Time", clock(), times);
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
    
    vector<vector<string>> data;
    ifstream infile("data.txt");
    while (infile)
    {
        string s;
        if (!getline(infile, s))
            break;

        istringstream ss(s);
        vector<string> record;

        while (ss)
        {
            string s;
            if (!getline(ss, s, ','))
                break;
            record.push_back(s);
        }

        data.push_back( record );
    }

    
    for (int i = 0; i < testSize; i++)
    {
        pubArray.push_back(Tag(data[0][i].c_str(),data[1][i].c_str()));
    }

    for(int i = 0; i < testSize; i++){
        subArray.push_back(Tag(data[0][i].c_str(),data[2][i].c_str(), true, false, '='));
    }
    // if (testSize <= 20){
    // } else {
    //     for(int i = 0; i < 20; i++){
    //         subArray.push_back(Tag(data[1][i].c_str(),data[1][i].c_str(), true, false, '='));
    //     }
    //     for(int i = 20; i < testSize; i++){
    //         subArray.push_back(Tag(randomString(10).c_str(),randomString(10).c_str(), false,false,'='));
    //     }
    // }
    vector<Gate*> gates;
    generateTree(subArray,gates);
    Gate* theRoot = gates.back();
    //Subscriber Tree
    Gate AND1(Gate::Type::AND, 1, false, 2, false);
    Gate OR1(Gate::Type::OR, &AND1, 0, false);
    Gate OR3(Gate::Type::OR, 3, false, 4, false);
    Gate OR4(Gate::Type::OR, &OR1, &OR3);

    OR4.makeParent();

    //KP-ABE
    PrivateParams priv;
    PublicParams pub;
    setup(attributeUniverse, pub, priv);

    //Make access policy from subscriber tree and generate key
    Node* root = new Node;
    *root = OR4.createABETree();
    auto key = keyGeneration(priv, *root);

    addTime("Init ", clock(), times);

    // Create an attribute-based secret (attributes 1 and 3).
    element_s secret;
    vector<int> encryptionAttributes{0, 1, 2, 3, 4};
    auto Cw = createSecret(pub, encryptionAttributes, secret);

    //Encrypt the message
    std::vector<uint8_t> ciphertext = encrypt(pub, encryptionAttributes, text, Cw);
    addTime("Encrypt of Payload by Pub", clock(), times);

    //Encryption of Interests
    for (int i = 0; i < subArray.size(); i++){
        subArray[i].genSubHash(betaKey);
    }
    addTime("Interests Encryption", clock(), times);

    //Generate r permutation and send to B2
    if (sodium_init() == -1)
    {
        printf("Sodium Library failed to initilise");
    }
    int r = randombytes_random();

    //From Sub to B1 - PRP
    interestPermutation(r, subArray);
    addTime("Permutation Time on Sub", clock(), times);

    //Encryption time of Tags
    for (int i = 0; i < pubArray.size(); i++){
        pubArray[i].genHash(betaKey);
    }
    addTime("Encrypt Of Tags", clock(), times);

    //Done by B1 - Search
    vector<bool> matches = matchInterests(pubArray, subArray);
    addTime("Search and  decryption time on B1", clock(), times);

    //Done by B2 - PRP Reverse
    interestPermutationReverse(r, matches);
    addTime("PRP reverse B2", clock(), times);

    //Send to B3 - Structure

    //Done by B3 - Evaluation of Tree
    int eval = theRoot->evaluate(matches);
    if (eval == 1) ;//cout << "Evaluated" << endl;
    else cout << "Evaluation Failiure" << endl;
    
    addTime("Evaluation of tree by B3", clock(), times);
    
    //Decryption of payload
    vector<int> testAttributes{0, 1, 2, 4};
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

vector<Timer> singleBrokerTest(string text, int testSize)
{
    vector<Timer> times = {};
    addTime("Launch Time", clock(), times);
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
    
    vector<vector<string>> data;
    ifstream infile("data.txt");
    while (infile)
    {
        string s;
        if (!getline(infile, s))
            break;

        istringstream ss(s);
        vector<string> record;

        while (ss)
        {
            string s;
            if (!getline(ss, s, ','))
                break;
            record.push_back(s);
        }

        data.push_back( record );
    }

    
    for (int i = 0; i < testSize; i++)
    {
        pubArray.push_back(Tag(data[0][i].c_str(),data[1][i].c_str()));
    }

    for(int i = 0; i < testSize; i++){
        subArray.push_back(Tag(data[0][i].c_str(),data[2][i].c_str(), true, false, '='));
    }

    vector<Gate*> gates;
    generateTree(subArray,gates);
    Gate* theRoot = gates.back();
    //Subscriber Tree
    Gate AND1(Gate::Type::AND, 1, false, 2, false);
    Gate OR1(Gate::Type::OR, &AND1, 0, false);
    Gate OR3(Gate::Type::OR, 3, false, 4, false);
    Gate OR4(Gate::Type::OR, &OR1, &OR3);

    OR4.makeParent();

    //KP-ABE
    PrivateParams priv;
    PublicParams pub;
    setup(attributeUniverse, pub, priv);

    //Make access policy from subscriber tree and generate key
    Node* root = new Node;
    *root = OR4.createABETree();
    auto key = keyGeneration(priv, *root);

    addTime("Init ", clock(), times);

    // Create an attribute-based secret (attributes 1 and 3).
    element_s secret;
    vector<int> encryptionAttributes{0, 1, 2, 3, 4};
    auto Cw = createSecret(pub, encryptionAttributes, secret);

    //Encrypt the message
    std::vector<uint8_t> ciphertext = encrypt(pub, encryptionAttributes, text, Cw);
    addTime("Encrypt of Payload by Pub", clock(), times);

    //Encryption of Interests
    for (int i = 0; i < subArray.size(); i++){
        subArray[i].genSubHash(betaKey);
    }
    addTime("Interests Encryption", clock(), times);

    //Encryption time of Tags
    for (int i = 0; i < pubArray.size(); i++){
        pubArray[i].genHash(betaKey);
    }
    addTime("Encrypt Of Tags", clock(), times);

    //Done by B1 - Search
    vector<bool> matches = matchInterestsSingleBroker(pubArray, subArray);
    addTime("Search and  decryption time on B1", clock(), times);

    //Send to B3 - Structure

    //Done by B3 - Evaluation of Tree
    int eval = theRoot->evaluate(matches);
    if (eval == 1) ;//cout << "Evaluated" << endl;
    else cout << "Evaluation Failiure" << endl;
    addTime("Evaluation of tree by B3", clock(), times);
    
    //Decryption of payload
    vector<int> testAttributes{0, 1, 2, 4};
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
    if (sodium_init() == -1){
        printf("Sodium Library failed to initilise");
    }
    srand (randombytes_random());
    string text = "";
    for(int i = 0; i < len; i++){
        int num = rand() % 70;
        text += alphanum[num];
    }
    return text;
}