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

    //List of Tags
    Tag pubTag1("name","Pramodya", betaKey);
    Tag pubTag2("lastName","De Alwis", betaKey);
    Tag pubTag3("sex","male", betaKey);
    Tag pubTag4("age","22", betaKey);
    Tag pubTag5("dob","15/06/1995", betaKey);

    //List of Interests
    Tag subInterest1("age","22",betaKey, false, '=');
    Tag subInterest2("sex","male",betaKey, false, '=');
    Tag subInterest3("dob","15/06/1995",betaKey, false, '=');

   
    //Arrays of Tags
    Tag pubArray[] = {
        Tag("paitiendID", "13216541", betaKey),
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
        Tag("paitiendID", "32131315", betaKey),
        Tag("name","Rhea", betaKey),
        Tag("middleName", "", betaKey),
        Tag("lastName","Babbar", betaKey),
        Tag("age","22", betaKey), 
        Tag("dob","02/01/1995", betaKey),
        Tag("occupation", "test analyst", betaKey),
        Tag("height", "165", betaKey),
        Tag("bloodType", "O", betaKey),
        Tag("sex","female", betaKey), 
    };

    //Array of interests
    Tag subArray[] = {
        Tag("name","Pramodya", betaKey, false, '='), 
        Tag("lastName","De Alwis", betaKey, false, '='), 
        Tag("dob","15/06/1995", betaKey, false, '='),
        Tag("occupation", "student", betaKey),
        Tag("sex","female", betaKey), 
        Tag("bloodType", "A+", betaKey),
    };


    // subArray[0].printTag();

    // pubTag2.printTag(true,false,true,false);
    // g = pubTag1;
    // g.printTag(true,false,true,false);

   
    if(sodium_init() == -1){
        printf("Sodium Library failed to initilise");
    }

    //Generate r permutation
    int r = randombytes_random();

    Tag AND1(AND, &subArray[0], true, &subArray[1], false);
    Tag AND2(AND, &subArray[3], true, &subArray[4], false);
    Tag OR1(OR, &AND1, &AND1);

    OR1.printTag();

    interestPermutation(r,subArray,3,false);


    // TESTING
    
    // subArray[0].printTag();

    // for (int i = 0; i < 3; i++){
    //     subArray[i].printTag(true,false,false,false);
    // }
        
}

