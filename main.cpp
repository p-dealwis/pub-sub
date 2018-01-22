using namespace std;

#include <gcrypt.h>
#include <sodium.h>
#include <iostream>

#include "pbc.h"
#include "Gate.h"
#include "Tag.h"
#include "pub_sub.h"
#include "kpabe.hpp"

int main(){
    // Initialise GCRYPT
    if (!gcry_check_version (GCRYPT_VERSION)){
        fputs ("libgcrypt version mismatch\n", stderr);
        exit (2);
    }

    /* A 256 bit key */
    uint8_t *betaKey = (unsigned char *)"01234567890123456789012345678901";
    uint8_t *permuteKey = (unsigned char *)"95651313544354956513135443549565";

    // vector<string> attributes {
    //     "paitientID",
    //     "name",
    //     "middleName",
    //     "lastName",
    //     "age",
    //     "dob",
    //     "occupation",
    //     "height",
    //     "bloodType",
    //     "sex"
    // };
    
    vector <int> attributeUniverse {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    //Arrays of Tags
    Tag pubArray[] = {
        Tag("paitientID", "13216541"),
        Tag("name","Pramodya"),
        Tag("middleName", "Dilan"),
        Tag("lastName","De Alwis"), 
        Tag("age","22"), 
        Tag("dob","15/06/1995"),
        Tag("occupation", "student"),
        Tag("height", "182"),
        Tag("bloodType", "A+"),
        Tag("sex","male"), 
    };

    Tag pubArray2[] = {
        Tag("paitientID", "32131315"),
        Tag("name","Rhea"),
        Tag("middleName", ""),
        Tag("lastName","Babbar"),
        Tag("age","23"), 
        Tag("dob","02/01/1995"),
        Tag("occupation", "test analyst"),
        Tag("height", "165"),
        Tag("bloodType", "O"),
        Tag("sex","female"), 
    };

    //Array of interests
    Tag subArray[] = {
        Tag("paitientID", "32131315", false,'='),
        Tag("name","Pramodya", false,'='),
        Tag("middleName", "", false,'='), 
        Tag("lastName","De Alwis", false,'='), 
        Tag("age","22", false,'='), 
        Tag("dob","15/06/1995", false,'='),
        Tag("occupation", "student", false,'='),
        Tag("height", "165", false,'='),
        Tag("bloodType", "A+", false,'='),
        Tag("sex","female", false, '='), 
    };

    string text = "Hello, my name is Pramodya";

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

    // Create an attribute-based secret (attributes 1 and 3).
    element_s secret;
    vector<int> encryptionAttributes {0, 1, 2, 3, 4};
    auto Cw = createSecret(pub, encryptionAttributes, secret);
    
    //Encrypt the message
    std::vector<uint8_t> ciphertext = encrypt(pub,encryptionAttributes,text,Cw);

    //Encryption of Interests
    genHashArray(betaKey, subArray, 10);

    if(sodium_init() == -1){
        printf("Sodium Library failed to initilise");
    }

    //Generate r permutation and send to B2
    int r = randombytes_random();
    
    //From Sub to B1 - PRP
    interestPermutation(r,subArray,10,false);

    //Encryption time of Tags
    genHashArray(betaKey, pubArray, 10);

    //TODO: Encryption of payload

    //Done by B1 - Search
    matchInterests(pubArray,10,subArray,10);

    //Done by B2 - PRP Reverse
    interestPermutation(r,subArray,10,true);

    //Send to B3 - Structure


    //Done by B3 - Evaluation of Tree
    cout << "Evaluation: " << AND2.evaluate(subArray) << endl;  

    //Decryption of payload
    // -->First make access policy from subscriber tree and generate key
    Node root = AND2.createABETree();
    auto key = keyGeneration(priv, root);
    vector<int> testAttributes {1,2,4};
    try{
        string result = decrypt(key, Cw, testAttributes, ciphertext);
        cout << result << endl;
    } catch(const UnsatError& e) {
        cout << "Decryption Error" << endl;
    }

}

