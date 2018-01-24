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
    vector<int> averageTimes(tests[0].size(),0);
    for (int i = 0; i < tests.size(); i++){
        for (int j = 0; j < tests[0].size(); j++){
            averageTimes[j] += tests[i][j].mseconds; 
        }
    }
    vector<Timer> average = {};
    for (int j = 0; j < tests[0].size(); j++){
        average.push_back(Timer(tests[0][j].name,averageTimes[j]/tests.size()));
    }
    return average;
}