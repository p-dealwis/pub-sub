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
    bool evaluate(vector<bool> &matches);
    void makeParent();
    void print(vector<Tag> &subArray);
    Gate(Type, int, bool, int, bool);
    Gate(Type, Gate *, int, bool);
    Gate(Type, Gate *, Gate *);
    Gate(int, bool = false);
    Gate(const Gate &other);
    Gate(){};
    Gate &operator=(const Gate &other);
    Node createABETree();

  private:
    bool _isLeftGate = true;
    bool _isRightGate = true;
    bool _parent = false;
    bool _valueOnly = false;
    Type _gateType = Gate::Type::OR;
    Gate *_leftGate = 0;
    Gate *_rightGate = 0;

    //Interest Info
    int _left = -1;
    int _right = -1;
    bool _leftNOT = false;
    bool _rightNOT = false;
};

#endif
