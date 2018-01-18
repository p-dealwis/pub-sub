using namespace std;

#include <string.h>
#include <iostream>

#include "Gate.h"

//TODO: Fix Evaluate
bool Gate::evaluate(Tag *subArray){
    if (_isLeftGate) return evaluate(subArray);
    else {
        bool left = subArray[_left].isMatch();
        cout << "LEFT BEFORE: " << left << endl;
        if (_leftNOT){
            if (left) left = false; else left = true;
        }
        cout << "LEFT NOT: " << _leftNOT << endl;
        cout << "LEFT: " << left << endl;
    }
    if (_isRightGate) return evaluate(subArray);
    else {
        bool right = subArray[_right].isMatch();
        cout << "RIGHT BEFORE: " << right << endl;
        if (_rightNOT) {
            if (right) right = false; else right = true;
        }
        cout << "RIGHT NOT: " << _rightNOT << endl;
        cout << "RIGHT: " << right << endl;
    } 
    if (_gateType == AND) return left && right;
    else{
        cout << "OR" << endl;
        return left || right;
    }
}


void Gate::makeParent(){
    _parent = true;
}

//Gate Constructor with 2 Interests
Gate::Gate(int type, int leftNum, bool leftNOT, int rightNum, bool rightNOT){
    _isLeftGate = false;
    _isRightGate = false;
    _gateType = type;
    _left = leftNum;
    _right = rightNum;
    _leftNOT = leftNOT;
    _rightNOT = rightNOT;
};

//Gate Constructor with 1 Gate and 1 Interest
Gate::Gate(int type, Gate* gate, int num, bool interestNOT){
    _isRightGate = false;
    _gateType = type;
    _leftGate = gate;
    _right = num;
    _rightNOT = interestNOT;
};

//Gate Constructor with 2 Gates
Gate::Gate(int type, Gate* leftGate, Gate* rightGate){
    _gateType = type;
    _leftGate = leftGate;
    _rightGate = rightGate;
};

/* ----------- DEBUG FUNCTIONS ----------- */

void Gate::print(Tag *subArray){
    string type;
    if (_gateType == AND) type = "AND"; else type = "OR";
    cout << "THIS IS AN " << type << " GATE" << endl;
    cout << "------------------------------------" << endl;
    if (!_isLeftGate) {
        if(_leftNOT) cout << "NOT" << endl;
        subArray[_left].print(true,true,false,false);
    }
    else _leftGate->print(subArray);
    if (!_isRightGate) {
        if(_leftNOT) cout << "NOT" << endl;
        subArray[_right].print(true,true,false,false);
    }
    else _rightGate->print(subArray);
    cout << "------------------------------------" << endl;
}