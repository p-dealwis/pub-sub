#ifndef PUB_SUB_H
#define PUB_SUB_H

#include <vector>
#include "Tag.h"
#include "Gate.h"
#include "test.hpp"

void interestPermutation(int seed, vector<Tag> &array);
void interestPermutationReverse(int seed, vector<bool> &array);
vector<bool>  matchInterests(vector<Tag> &pubArray, vector<Tag> &subArray);
vector<bool> optimisedMatching(vector<vector<Tag>> &searchArray, vector<Tag> &subArray);
void storeTags(vector<Tag> &pubArray,vector<vector<Tag>> &searchArray);
vector<bool>  matchInterestsSingleBroker(vector<Tag> &pubArray, vector<Tag> &subArray);
void printArray(vector<Tag> &array);
void saveResults(string filename, vector<Tests> results);
Gate* generateTree(vector<Tag> &subArray, vector<Gate*> &gates);
Gate* generateRoot(vector<Gate*> &gateArray, int  = 0);

#endif
