#ifndef STRUCTURE_H
#define STRUCTURE_H

#include "Tag.h"


class Structure {
public:
    Structure(Tag* contained,Tag* left,Tag* right);
    Structure(Tag* contained);
    makeStructure(Tag []);
private:
    Tag _contained;
    Tag _left;
    Tag _right;
    bool _isParent = false;
};


#endif