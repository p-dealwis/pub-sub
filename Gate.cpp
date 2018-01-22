using namespace std;

#include <string.h>
#include <iostream>

#include "Gate.h"

bool Gate::evaluate(Tag *subArray)
{
    bool l = false, r = false;
    if (_isLeftGate)
        l = _leftGate->evaluate(subArray);
    else
    {
        l = subArray[_left].isMatch();
        if (_leftNOT)
        {
            if (l)
                l = false;
            else
                l = true;
        }
    }
    if (_isRightGate)
        r = _rightGate->evaluate(subArray);
    else
    {
        r = subArray[_right].isMatch();
        if (_rightNOT)
        {
            if (r)
                r = false;
            else
                r = true;
        }
    }
    if (_gateType == Type::AND)
    {
        if (l && r)
            return true;
        else
            return false;
    }
    else
    {
        if (l || r)
            return true;
        else
            return false;
    }
}

void Gate::makeParent()
{
    _parent = true;
}

//Gate Constructor with 2 Interests
Gate::Gate(Type type, int leftNum, bool leftNOT, int rightNum, bool rightNOT)
{
    _isLeftGate = false;
    _isRightGate = false;
    _gateType = type;
    _left = leftNum;
    _right = rightNum;
    _leftNOT = leftNOT;
    _rightNOT = rightNOT;
};

//Gate Constructor with 1 Gate and 1 Interest
Gate::Gate(Type type, Gate *gate, int num, bool interestNOT)
{
    _isRightGate = false;
    _gateType = type;
    _leftGate = gate;
    _right = num;
    _rightNOT = interestNOT;
};

//Gate Constructor with 2 Gates
Gate::Gate(Type type, Gate *leftGate, Gate *rightGate)
{
    _gateType = type;
    _leftGate = leftGate;
    _rightGate = rightGate;
};

/* ----------- DEBUG FUNCTIONS ----------- */

void Gate::print(Tag *subArray)
{
    string type;
    if (_gateType == Type::AND)
        type = "AND";
    else
        type = "OR";
    cout << "THIS IS AN " << type << " GATE" << endl;
    cout << "------------------------------------" << endl;
    if (!_isLeftGate)
    {
        if (_leftNOT)
            cout << "NOT" << endl;
        subArray[_left].print(true, true, false, false);
    }
    else
        _leftGate->print(subArray);
    if (!_isRightGate)
    {
        if (_leftNOT)
            cout << "NOT" << endl;
        subArray[_right].print(true, true, false, false);
    }
    else
        _rightGate->print(subArray);
    cout << "------------------------------------" << endl;
}

Node Gate::createABETree()
{
    int l, r;
    Node::Type type = _gateType == Type::AND ? Node::Type::AND : Node::Type::OR;
    if (_isRightGate)
    {
        return Node(type, {_leftGate->createABETree(), _rightGate->createABETree()});
    }
    else if (_isLeftGate)
    {
        return Node(type, {_leftGate->createABETree(), Node(_right)});
    }
    else
    {
        return Node(type, {Node(_left), Node(_right)});
    }
}