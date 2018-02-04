using namespace std;

#include <iostream>
#include <time.h>
#include <vector>

#include "Timer.hpp"
#include "test.hpp"
#include "pub_sub.h"

#define KB 1024
#define MB KB*KB

vector<int> case1 = {KB,MB, MB*2,MB*4,MB*8,MB*16};
vector<int> case2 = {MB*32,MB*64};
vector<int> case3 = {MB*128};
vector<int> allCases = {KB,MB, MB*2,MB*4,MB*8,MB*16,MB*32,MB*64,MB*128};
vector<vector<int>> testCases = {case1,case2,case3,allCases};

vector<int> extraTests = {70, 80, 90, 100, 110, 116};

int main(int argc, char *argv[])
{
    int NUM_TESTS = 100;
    string filename = "results.txt";
    if ( argc < 2 ) {
        cout<<"Needs atleast 1 argument: testCase number (1-4)"<< endl;
        return 0;
    } 
    if ( argc >= 3 ) {
        NUM_TESTS = atoi(argv[2]);
    }
    if ( argc == 4 ) {
        filename = argv[3];
    } 
    int testNum = atoi(argv[1]);
    cout << "    -------------------------------"<<  endl;
    cout << "Testcase Number: " << testNum<<  endl;
    cout << "Tests per run: " << NUM_TESTS <<  endl;
    cout << "Outputting to: " << filename <<  endl;
    cout << "    -------------------------------"<<  endl;
    vector<Tests> results = {};
    for (int i = 0; i < testCases[testNum].size(); i++){
        cout << "    -------------------------------"<<  endl;
        cout << "Started calculating for message encryption size: " << testCases[testNum][i]/1024 << "KB" << endl;
        for (int j = 1; j <= 20; j++){
            cout << "Tags: " << j << endl;
            vector<vector<Timer>> tests = {};
            for(int k = 0; k < NUM_TESTS; k++){
                vector<Timer> trial = singleBrokerTest(randomString(testCases[testNum][i]), j);
                tests.push_back(trial);
            }
            vector<Timer> average = averageArray(tests);
            cout << "Average time for tests: " << average.back().mseconds << "ms" << endl;
            cout << "Average time for tests without initialisation time: " << average[average.size()-2].mseconds << "ms" << endl;
            results.push_back(Tests(average, testCases[testNum][i], j));
        }
        int j;
        for( int l = 0; l < extraTests.size(); l++){
            j = extraTests[l];
            cout << "Tags: " << j << endl;
            vector<vector<Timer>> tests = {};
            for(int k = 0; k < NUM_TESTS; k++){
                vector<Timer> trial = singleBrokerTest(randomString(testCases[testNum][i]), j);
                tests.push_back(trial);
            }
            vector<Timer> average = averageArray(tests);
            cout << "Average time for tests: " << average.back().mseconds << "ms" << endl;
            cout << "Average time for tests without initialisation time: " << average[average.size()-2].mseconds << "ms" << endl;
            results.push_back(Tests(average, testCases[testNum][i], j));
        }

    }
    saveResults(filename, results);
    cout << "DONE" << endl;

}
