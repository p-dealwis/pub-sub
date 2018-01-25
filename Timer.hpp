#ifndef TIMER_H
#define TIMER_H

#include <time.h>
#include <iostream>
#include <vector>

using namespace std;

class Timer{
private:
    clock_t t;
    float diff;
    clock_t zero;

public:
    float mseconds;
    string name;

    Timer(string name, clock_t t, clock_t prevTime){
        this->t = t;
        this->diff = (float)t - (float) prevTime;
        this->name = name;
        this->mseconds = (diff/CLOCKS_PER_SEC)*1000;
    }

    Timer(string name, float mseconds){
        this->name = name;
        this->mseconds = mseconds;
    }

    Timer& operator=(const Timer &other){
        this->t = other.t;
        this->diff = other.diff;
        this->name = other.name;
        this->mseconds = other.mseconds;
    }

    clock_t retTime(){
        return t;
    }

    void print(){
        cout << name << ": " << mseconds << "ms" << endl;
    }

};

void addTime(string name, clock_t t, vector<Timer> &times);
void printTimes(vector<Timer> &times, int start, int end);
void totalTime(vector<Timer> &times, bool includeInit = true);
vector<Timer> averageArray(vector<vector<Timer>> &tests);

#endif