#ifndef PUB_SUB_H
#define PUB_SUB_H

#include <vector>
#include "Tag.h"
#include "test.hpp"

void interestPermutation(int seed, vector<Tag> &array, bool inverse = false);
void matchInterests(vector<Tag> &pubArray, vector<Tag> &subArray);
void printArray(vector<Tag> &array);
void saveResults(string filename, vector<Tests> results);

#endif