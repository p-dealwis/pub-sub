#ifndef TEST_H
#define TEST_H
#include <vector>
#include "Timer.hpp"
using namespace std;


class Tests:
public:
    vector<Timer> Timers;
    int dataSize;
    int tagSize;

    Tests(vector<Timer> &Timers, int dataSize, int tagSize){
        this->Timers = Timers;
        this->dataSize = dataSize;
        this->tagSize = tagSize;
    }
};

vector<Timer> test(string text, int testSize);
string randomString(int len);

#endif