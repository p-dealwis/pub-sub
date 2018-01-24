#include "Timer.hpp"
#include <time.h>
#include <vector>

using namespace std;

void addTime(string name, clock_t t, vector<Timer> &times){
    if (times.size() > 0){
        Timer test = times.back();
        times.push_back(Timer(name,t,times.back().retTime()));
    } else {
        times.push_back(Timer(name,t,0));
    }
}

void totalTime(vector<Timer> &times, bool includeInit){
    if (includeInit){
        times.push_back(Timer("Total Time",times.back().retTime(),0));
    } else {
        times.push_back(Timer("Total Time without Init",times.back().retTime(),times.front().retTime()));
    }
}

void printTimes(vector<Timer> &times, int start, int end){
    for(int i = start; i < end; i++){
        times[i].print();
    }
}

vector<Timer> averageArray(vector<vector<Timer>> &tests){
    int testLen = tests[0].size();
    vector<float> testTimes(testLen,0);
    for (int i = 0; i < tests.size(); i++){
        for (int j = 0; j < testLen; j++){
            testTimes[j] += tests[i][j].mseconds; 
        }
    }
    vector<Timer> average = {};
    for (int j = 0; j < testLen; j++){
        string name = tests[0][j].name;
        float aveTime = testTimes[j]/tests.size();
        average.push_back(Timer(name, aveTime));
    }
    return average;
}