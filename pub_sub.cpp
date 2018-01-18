using namespace std;

#include <utility>
#include <iostream>

#include "pub_sub.h"
#include "Tag.h"

/*  Permutes an subscriber interest objects 
*   @param seed - integer
*   @param array - array of subscriber interest objects 
*   @param len - length of array
*   @param inverse - get original order
*   TESTED CONFIRMED WORKING
*/
void interestPermutation(int seed, Tag *array, int len, bool inverse){
    int j;
    if (len > 1) {
        int i;
        if (inverse == true){
            for (i = len - 1; i > 0; i--) {
                j = seed % i;
                if( j < 0){
                    j = 0 - j;
                }
                Tag t = move(array[j]);
                array[j] = move(array[i]);
                array[i] = move(t);
            }
        } else{
            for (i = 1; i < len; i++) {
                j = seed % i;
                if( j < 0){
                    j = 0 - j;
                }
                Tag t = move(array[j]);
                array[j] = move(array[i]);
                array[i] = move(t);
            }
        }
    }
}

void matchInterests(Tag *pubArray, int pubLen, Tag *subArray, int subLen){
    int i,j;
    for (j = 0; j < subLen; j++){
        for (i = 0; i < pubLen; i++){
            if(pubArray[i] == subArray[j]) {
                subArray[j].matched();
                break;
            }
        }
    }
}