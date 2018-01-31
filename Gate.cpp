using namespace std;

#include <string.h>
#include <iostream>

#include "Gate.h"

bool Gate::evaluate(vector<bool> &matches)
{
    this;
    bool l = false, r = false;
    if(_valueOnly){
        l = matches[_left];
        if (_leftNOT)
        {
            if (l)
                l = false;
            else
                l = true;
        }
        return l;
    }
    if (_isLeftGate)
        l = _leftGate->evaluate(matches);
    else
    {
        l = matches[_left];
        if (_leftNOT)
        {
            if (l)
                l = false;
            else
                l = true;
        }
    }
    if (_isRightGate)
        r = _rightGate->evaluate(matches);
    else
    {
        r = matches[_right];
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
    if(rightGate->_valueOnly){
        _isRightGate = false;
        _right = rightGate->_left;
    } else {
        _rightGate = rightGate;
    }
    if(leftGate->_valueOnly){
        _isLeftGate = false;
        _left = leftGate->_left;
    } else {
        _leftGate = leftGate;
    }
    
};

Gate::Gate(int value, bool NOT){
    _left = value;
    _leftNOT = NOT;
    _valueOnly = true;
    _isLeftGate = false;
    _isRightGate = false;
}

//Copy Constructor
Gate::Gate(const Gate &other){
    _isLeftGate = other._isLeftGate;
    _isRightGate = other._isRightGate;
    _parent = other._parent;
    _valueOnly = other._valueOnly;
    _gateType = other._gateType;
    _leftGate = other._leftGate;
    _rightGate = other._rightGate;

    _left = other._left;
    _right = other._right;
    _leftNOT = other._leftNOT;
    _rightNOT = other._rightNOT;
}

//Copy Assignment
Gate &Gate::operator=(const Gate &other){
    _isLeftGate = other._isLeftGate;
    _isRightGate = other._isRightGate;
    _parent = other._parent;
    _valueOnly = other._valueOnly;
    _gateType = other._gateType;
    _leftGate = other._leftGate;
    _rightGate = other._rightGate;

    _left = other._left;
    _right = other._right;
    _leftNOT = other._leftNOT;
    _rightNOT = other._rightNOT;
}

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
    Node::Type type = _gateType == Type::AND ? Node::Type::AND : Node::Type::OR;
    if (_isLeftGate && _isRightGate)
    {
        return Node(type, {_leftGate->createABETree(), _rightGate->createABETree()});
    }
    else if (!_isLeftGate && _isRightGate)
    {
        return Node(type, {Node(_left), _rightGate->createABETree()});
    } 
    else if (_isLeftGate && !_isRightGate)
    {
        return Node(type, {_leftGate->createABETree(), Node(_right)});
    }
    else
    {
        if(_right = -1){
             return Node(_left);   
        } else{
            return Node(type, {Node(_left), Node(_right)});
        }
    }
}