#ifndef PUB_SUB_H
#define PUB_SUB_H

#include "Tag.h"

void interestPermutation(int seed, Tag *array, int len, bool inverse = false);
void matchInterests(Tag *pubArray, int pubLen, Tag *subArray, int subLen);

#endif