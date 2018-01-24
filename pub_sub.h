#ifndef PUB_SUB_H
#define PUB_SUB_H

#include <vector>
#include "Tag.h"

void createTagArray(string fileName, int len, vector<Tag> &pubArray, vector<Tag> &subArray);
void interestPermutation(int seed, vector<Tag> &array, bool inverse = false);
void matchInterests(vector<Tag> &pubArray, vector<Tag> &subArray);
void genHashArray(uint8_t *key, vector<Tag> &array);
void printArray(vector<Tag> &array);

#endif