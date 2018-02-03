using namespace std;

#include <utility>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

#include "pub_sub.h"
#include "Tag.h"
#include "Gate.h"

/*  Permutes an subscriber interest objects 
*   @param seed - integer
*   @param array - array of subscriber interest objects 
*   @param len - length of array
*   @param inverse - get original order
*   TESTED CONFIRMED WORKING
*/
void interestPermutation(int seed, vector<Tag> &array)
{
    int j;
    int len = array.size();
    if (len > 1)
    {
        int i;
        for (i = len - 1; i > 0; i--)
        {
            j = seed % i;
            if (j < 0)
            {
                j = 0 - j;
            }
            iter_swap(array.begin()+j, array.begin()+i);
        }
    }
}

void interestPermutationReverse(int seed, vector<bool> &array)
{
    int j;
    int len = array.size();
    if (len > 1)
    {
        int i;
        for (i = 1; i < len; i++)
        {
            j = seed % i;
            if (j < 0)
            {
                j = 0 - j;
            }
            iter_swap(array.begin()+j, array.begin()+i);
        }
    }
}

vector<bool> matchInterests(vector<Tag> &pubArray, vector<Tag> &subArray)
{
    int i, j;
    vector<bool> matches(subArray.size(),false);
    for (j = 0; j < subArray.size(); j++)
    {
        for (i = 0; i < pubArray.size() ; i++)
        {
            if (pubArray[i] == subArray[j]){
                if(pubArray[i].compareRHash(subArray[j])){
                    matches[j] = true;
                }
                break;
            }
        }
    }
    return matches;
}

vector<bool> matchInterestsSingleBroker(vector<Tag> &pubArray, vector<Tag> &subArray)
{
    int i, j;
    vector<bool> matches(subArray.size(),false);
    for (j = 0; j < subArray.size(); j++)
    {
        for (i = 0; i < pubArray.size() ; i++)
        {
            if(pubArray[i].compareRHash(subArray[j])){
                matches[j] = true;
                break;
            }
        }
    }
    return matches;
}

void printArray(vector<Tag> &array)
{
    for (int i = 0; i < array.size(); i++)
    {
        array[i].print(true,false,false,false,false);
    }
}

void saveResults(string filename, vector<Tests> results){
    ofstream ofs(filename, std::ofstream::out);
    //Headers
    ofs << "Data Size(KB),No. Tags," ;
    for (int i = 0; i < results[0].Timers.size(); i++){
        ofs << results[0].Timers[i].name << "," ;
    }
    ofs << endl;

    //Write Data
    for(int j = 0; j < results.size(); j++){
        ofs << results[j].dataSize/1024 << "," << results[j].tagSize << ",";
        for (int k = 0; k < results[k].Timers.size(); k++){
            ofs << results[j].Timers[k].mseconds << ",";
        }
        ofs << endl;
    }
    ofs.close();
}


Gate* generateTree(vector<Tag> &subArray, vector<Gate*> &gates){
    //Initialise make gates from subArray
    for(int i = 0; i < subArray.size() - subArray.size()/2; i++){
        //First = i * 2 Second = i * 2 + 1
        if(subArray.size()%2 != 0 && i*2 + 1 >= subArray.size()){
            gates.push_back(new Gate(i*2));
        } else if(subArray[i * 2].isReal() && subArray[i * 2 + 1].isReal()){
            gates.push_back(new Gate(Gate::Type::AND,i*2,false,i*2+1,false));
        } else if(subArray[i * 2].isReal() || subArray[i * 2 + 1].isReal()){
            gates.push_back(new Gate(Gate::Type::OR,i*2,false,i*2+1,true));
        } else {
        gates.push_back(new Gate(Gate::Type::OR,i*2,true,i*2+1,false));
        }
    }
    //TODO: Recursively make tree from array of gates
    return generateRoot(gates);
}

Gate* generateRoot(vector<Gate*> &gateArray, int pos){
    int initialSize = gateArray.size();
    if (initialSize - pos <= 1){
        return gateArray.back();
    }
    for(int i = pos; i < initialSize - initialSize%2; i = i + 2){
        gateArray.push_back(new Gate(Gate::Type::OR, gateArray[i], gateArray[i+1]));
    };
    return generateRoot(gateArray, pos + initialSize - initialSize%2);
}


