using namespace std;

#include <gcrypt.h>
#include <stdio.h>
#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <sodium.h>
#include <utility>

#include <iostream>

#include "Gate.h"
#include "Tag.h"
#include "pub_sub.h"


int main(){
    // Initialise GCRYPT
    if (!gcry_check_version (GCRYPT_VERSION)){
        fputs ("libgcrypt version mismatch\n", stderr);
        exit (2);
    }

    /* A 256 bit key */
    uint8_t *betaKey = (unsigned char *)"01234567890123456789012345678901";
    uint8_t *permuteKey = (unsigned char *)"95651313544354956513135443549565";

    // //List of Tags
    // Tag pubTag1("name","Pramodya");
    // Tag pubTag2("lastName","De Alwis");
    // Tag pubTag3("sex","male");
    // Tag pubTag4("age","22");
    // Tag pubTag5("dob","15/06/1995");

    // //List of Interests
    // Tag subInterest1("age","22, false, '=');
    // Tag subInterest2("sex","male, false, '=');
    // Tag subInterest3("dob","15/06/1995, false, '=');

   
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


    // subArray[0].print();

    // pubTag2.print(true,false,true,false);
    // g = pubTag1;
    // g.print(true,false,true,false);

    // if(pubArray[0] == subArray[0]) subArray[0].matched();
    // cout << subArray[0].isMatch() << endl;


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
    Gate OR1(OR, 0, true, 1, true);
    Gate AND1(AND, 2, false, 3, false);

    Gate TEST(OR, &OR1, &AND1);

    Gate AND2(OR, &OR1, &AND1);

    Gate AND3(AND, 4, true, 5, false);
    Gate OR2(OR, &AND2, &AND3);
    
    OR2.makeParent();
    
    //Done by B3 - Evaluation of Tree
    cout << "Evaluation: " << OR2.evaluate(subArray) << endl;  

    //TODO: Decryption of payload


    // TESTING
    
    // OR2.print(subArray);

    // subArray[0].print();

    // for (int i = 0; i < 10; i++){
    //     subArray[i].print(true,false,false,false,true);
    // }

}

