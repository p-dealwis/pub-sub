using namespace std;

#include <utility>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

#include "pub_sub.h"
#include "Tag.h"

/*  Permutes an subscriber interest objects 
*   @param seed - integer
*   @param array - array of subscriber interest objects 
*   @param len - length of array
*   @param inverse - get original order
*   TESTED CONFIRMED WORKING
*/
void interestPermutation(int seed, vector<Tag> &array, bool inverse)
{
    int j;
    int len = array.size();
    if (len > 1)
    {
        int i;
        if (inverse == true)
        {
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
        else
        {
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
}

void matchInterests(vector<Tag> &pubArray, vector<Tag> &subArray)
{
    int i, j;
    for (j = 0; j < subArray.size(); j++)
    {
        for (i = 0; i < pubArray.size() ; i++)
        {
            if (pubArray[i] == subArray[j])
            {
                subArray[j].matched();
                break;
            }
        }
    }
}


void printArray(vector<Tag> &array)
{
    for (int i = 0; i < array.size(); i++)
    {
        array[i].print(true,true,false,false,false);
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
        ofs << results[j].dataSize/1000 << "," << results[j].tagSize << ",";
        for (int k = 0; k < results[k].Timers.size(); k++){
            ofs << results[j].Timers[k].mseconds << ",";
        }
        ofs << endl;
    }
}