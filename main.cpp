using namespace std;

#include <iostream>
#include <time.h>
#include <vector>

#include "Timer.hpp"
#include "test.hpp"

#define KB 1000
#define MB 1000000
#define NUM_TESTS 1

// vector<int> number = {KB,MB,MB*2,MB*4,MB*8,MB*16,MB*32,MB*64,MB*128};
vector<int> number = {KB,MB,MB*2};

int main()
{
    vector<Tests> results = {};
    for (int i = 0; i < number.size(); i++){
        for (int j = 1; j <= 20; j++){
            vector<vector<Timer>> tests = {};
            for(int k = 0; k <= NUM_TESTS; k++){
                vector<Timer> trial = test(randomString(number[i]), j);
                tests.push_back(trial);
            }
            vector<Timer> average = averageArray(tests);
            
            results.push_back(Tests blah= {average, i, j});
        }   
    }
    cout << "DONE" << endl;
}
