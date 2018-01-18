#ifndef GATE_H
#define GATE_H

#include "Tag.h"

#define AND 0
#define OR 1

class Gate {
public:
    bool evaluate(Tag *subArray);
    void makeParent();
    void print(Tag *subArray);
    Gate(int, int, bool, int, bool);
    Gate(int, Gate*, int, bool);
    Gate(int, Gate*, Gate*);

private:
    bool _gateValue;
    bool _isLeftGate = true;
    bool _isRightGate = true;
    bool _parent = false;
    int _gateType;
    Gate* _leftGate;
    Gate* _rightGate;

    //Interest Info
    int _left;
    int _right;
    bool _leftNOT;
    bool _rightNOT;
};

#endif