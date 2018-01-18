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
    // Tag pubTag1("name","Pramodya", betaKey);
    // Tag pubTag2("lastName","De Alwis", betaKey);
    // Tag pubTag3("sex","male", betaKey);
    // Tag pubTag4("age","22", betaKey);
    // Tag pubTag5("dob","15/06/1995", betaKey);

    // //List of Interests
    // Tag subInterest1("age","22",betaKey, false, '=');
    // Tag subInterest2("sex","male",betaKey, false, '=');
    // Tag subInterest3("dob","15/06/1995",betaKey, false, '=');

   
    //Arrays of Tags
    Tag pubArray[] = {
        Tag("paitientID", "13216541", betaKey),
        Tag("name","Pramodya", betaKey),
        Tag("middleName", "Dilan", betaKey),
        Tag("lastName","De Alwis", betaKey), 
        Tag("age","22", betaKey), 
        Tag("dob","15/06/1995", betaKey),
        Tag("occupation", "student", betaKey),
        Tag("height", "182", betaKey),
        Tag("bloodType", "A+", betaKey),
        Tag("sex","male", betaKey), 
    };

    Tag pubArray2[] = {
        Tag("paitientID", "32131315", betaKey),
        Tag("name","Rhea", betaKey),
        Tag("middleName", "", betaKey),
        Tag("lastName","Babbar", betaKey),
        Tag("age","23", betaKey), 
        Tag("dob","02/01/1995", betaKey),
        Tag("occupation", "test analyst", betaKey),
        Tag("height", "165", betaKey),
        Tag("bloodType", "O", betaKey),
        Tag("sex","female", betaKey), 
    };

    //Array of interests
    Tag subArray[] = {
        Tag("paitientID", "32131315", betaKey, false,'='),
        Tag("name","Pramodya", betaKey, false,'='),
        Tag("middleName", "", betaKey, false,'='), 
        Tag("lastName","De Alwis", betaKey, false,'='), 
        Tag("age","22", betaKey, false,'='), 
        Tag("dob","15/06/1995", betaKey, false,'='),
        Tag("occupation", "student", betaKey, false,'='),
        Tag("height", "165", betaKey, false,'='),
        Tag("bloodType", "A+", betaKey, false,'='),
        Tag("sex","female", betaKey, false, '='), 
    };


    // subArray[0].print();

    // pubTag2.print(true,false,true,false);
    // g = pubTag1;
    // g.print(true,false,true,false);

    // if(pubArray[0] == subArray[0]) subArray[0].matched();
    // cout << subArray[0].isMatch() << endl;

    if(sodium_init() == -1){
        printf("Sodium Library failed to initilise");
    }

    //Generate r permutation and send to B2
    int r = randombytes_random();

    //From Sub to B1 - PRP
    interestPermutation(r,subArray,10,false);

    //Done by B1 - Search
    matchInterests(pubArray,10,subArray,10);

    //Done by B2 - PRP Reverse
    interestPermutation(r,subArray,10,true);

    //Send to B3 - Structure
    Gate OR1(AND, 0, false, 1, true);
    Gate AND1(AND, 2, true, 3, false);
    Gate AND2(OR, &OR1, &AND1);

    Gate AND3(AND, 4, true, 5, false);
    Gate OR2(OR, &AND2, &AND3);
    
    OR2.makeParent();
    // OR2.print(subArray);

    // TESTING
    
    // subArray[0].print();

    for (int i = 0; i < 10; i++){
        subArray[i].print(true,false,false,false,true);
    }

    //Done by B3 - Evaluation of Tree
    // printf("%d", OR1.evaluate(subArray));
    cout << "Evaluation: " << OR1.evaluate(subArray) << endl;     
}

