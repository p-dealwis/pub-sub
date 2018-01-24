#ifndef GATE_H
#define GATE_H

#include "Tag.h"
#include "kpabe.hpp"

class Gate
{
  public:
    enum Type
    {
        OR,
        AND
    };

  public:
    bool evaluate(vector<Tag> &subArray);
    void makeParent();
    void print(Tag *subArray);
    Gate(Type, int, bool, int, bool);
    Gate(Type, Gate *, int, bool);
    Gate(Type, Gate *, Gate *);
    Node createABETree();

  private:
    bool _gateValue;
    bool _isLeftGate = true;
    bool _isRightGate = true;
    bool _parent = false;
    Type _gateType;
    Gate *_leftGate;
    Gate *_rightGate;

    //Interest Info
    int _left;
    int _right;
    bool _leftNOT;
    bool _rightNOT;
};

#endif