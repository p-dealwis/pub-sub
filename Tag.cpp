using namespace std;
#include <string.h>
#include <iostream>

#include "Tag.h"
#include "hash.h"

// == Operator
bool Tag::operator==(const Tag& other) {
    bool attrBool = memcmp(_attrHash, other._attrHash, HASH_SIZE) == 0;
    bool valBool = memcmp(_valHash, other._valHash, HASH_SIZE) == 0;
    if (_not) attrBool = !attrBool;
    if (other._not) valBool = !valBool;
    return attrBool && valBool;
}

//Gives an interest NOT logic
void Tag::makeNOT(){
    _not = true;
}

void Tag::makeParent(){
    _parent = true;
}

//Search and compare
bool Tag::checkValue(Tag* otherLeftTag, Tag* otherRightTag){
    bool left = *otherLeftTag == *_left;
    bool right = *otherRightTag == *_right;
    if (_gateType == AND) return left && right;
    else return left || right;
}

//Matched
void Tag::matched(){
    _match = true;
}

/*  Generates a hash for both the attribute and val and then stores it in the 
*   Tag structure.
*   @param tag - a Tag object
*   @param key - private key
*/
void Tag::genHash(uint8_t *key){
    KeyedHash(key, HASH_SIZE, (uint8_t*) _attr,_attrLen, _attrHash, HASH_SIZE);
    KeyedHash(key, HASH_SIZE, (uint8_t*) _val, _valLen, _valHash, HASH_SIZE);
}


/* ----------- CONTRUCTORS ----------- */

//Interest Constructor
Tag::Tag(const char * newAttr, const char * newVal, uint8_t* key, int interestNum, char opr){
    strcpy(_attr, newAttr);
    strcpy(_val, newVal);
    _attrLen = strlen(newAttr);
    _valLen = strlen(newVal);
    _isPublisher = false;
    _interestNum = interestNum;
    _opr = opr;
    genHash(key);
}

//Tag Constructor
Tag::Tag(const char * newAttr, const char * newVal, uint8_t* key){
    strcpy(_attr, newAttr);
    strcpy(_val, newVal);
    _attrLen = strlen(newAttr);
    _valLen = strlen(newVal);
    genHash(key);
}

//Empty Constructor
Tag::Tag(){};

//Gate Constructor with 2 Interests
Tag::Tag(int type, Tag* left, bool leftNOT, Tag* right, bool rightNOT){
    _isGate = true;
    _gateType = type;
    _left = left;
    _right = right;
    if (leftNOT) _left->makeNOT();
    if (rightNOT) _right->makeNOT();
};

//Gate Constructor with 1 Gate and 1 Interest
Tag::Tag(int type, Tag* gate, Tag* interest, bool interestNOT){
    _isGate = true;
    _gateType = type;
    _left = gate;
    _right = interest;
    if (interestNOT) _right->makeNOT();
};

//Gate Constructor with 2 Gates
Tag::Tag(int type, Tag* left, Tag* right){
    _isGate = true;
    _gateType = type;
    _left = left;
    _right = right;
};

//Deconstructor
Tag::~Tag(){};

//Copy Constructor
Tag::Tag(const Tag& other){
    //Copy Attributes and Values
    memcpy(_attr, other._attr, INPUT_SIZE);
    memcpy(_val, other._val, INPUT_SIZE);

    //Copy Hashes of attributes and values
    memcpy( _attrHash, other._attrHash, HASH_SIZE);
    memcpy( _valHash, other._valHash, HASH_SIZE);    

    //Copy Attributes and Value lengths
    _attrLen = other._attrLen;
    _valLen = other._valLen;

    //Remaining stuff copied
    _isPublisher = other._isPublisher;
    _opr = other._opr;
}

//Copy Assignment
Tag& Tag::operator=(const Tag& other){
    //Delete Old elements
    memset(_attr,0,INPUT_SIZE);
    memset(_val,0,INPUT_SIZE);
    memset(_attrHash,0,HASH_SIZE);
    memset(_valHash,0,HASH_SIZE);

    //Copy Attributes and Values
    memcpy(_attr, other._attr, INPUT_SIZE);
    memcpy(_val, other._val, INPUT_SIZE);

    //Copy Hashes of attributes and values
    memcpy( _attrHash, other._attrHash, HASH_SIZE);
    memcpy( _valHash, other._valHash, HASH_SIZE);    

    //Copy Attributes and Value lengths
    _attrLen = other._attrLen;
    _valLen = other._valLen;

    //Remaining stuff copied
    _isPublisher = other._isPublisher;
    _opr = other._opr;
}

//Move Contructor
Tag::Tag(Tag&& other){
    //Move Attributes and Values
    memcpy(_attr, other._attr,INPUT_SIZE);
    memcpy(_val, other._val, INPUT_SIZE);
    memset(other._attr, 0,INPUT_SIZE);
    memset(other._val, 0, INPUT_SIZE);

    //Copy Hashes of attributes and values
    memcpy( _attrHash, other._attrHash, HASH_SIZE);
    memcpy( _valHash, other._valHash, HASH_SIZE);
    memset(other._attrHash, 0,HASH_SIZE);
    memset(other._valHash, 0, HASH_SIZE);    

    //Copy Attributes and Value lengths
    _attrLen = other._attrLen;
    _valLen = other._valLen;
    other._attrLen = 0;
    other._valLen = 0;

    //Remaining stuff copied
    _isPublisher = other._isPublisher;
    _opr = other._opr;

    other._isPublisher = 0;
    other._opr = 0;
}

//Move Assignment
Tag& Tag::operator=(Tag&& other){
    //Delete old elements
    memset(_attr, 0,INPUT_SIZE);
    memset(_val, 0, INPUT_SIZE);
    memset(_attrHash, 0,HASH_SIZE);
    memset(_valHash, 0, HASH_SIZE);   

    //Move Attributes and Values
    memcpy(_attr, other._attr,INPUT_SIZE);
    memcpy(_val, other._val, INPUT_SIZE);
    memset(other._attr, 0,INPUT_SIZE);
    memset(other._val, 0, INPUT_SIZE);

    //Copy Hashes of attributes and values
    memcpy( _attrHash, other._attrHash, HASH_SIZE);
    memcpy( _valHash, other._valHash, HASH_SIZE);
    memset(other._attrHash, 0,HASH_SIZE);
    memset(other._valHash, 0, HASH_SIZE);    

    //Copy Attributes and Value lengths
    _attrLen = other._attrLen;
    _valLen = other._valLen;
    other._attrLen = 0;
    other._valLen = 0;

    //Remaining stuff copied
    _isPublisher = other._isPublisher;
    _opr = other._opr;

    other._isPublisher = 0;
    other._opr = 0;
}

/* ----------- DEBUG FUNCTIONS ----------- */

/*Prints out all important tag information
*/
void Tag::printTag(bool attr, bool val, bool attrHash, bool valHash, bool extra){
    if (_isGate){
        printGateVariables();
    } else {
        cout << "       --------------------       " << endl;
        if (_isPublisher) cout << "THIS IS A TAG" << endl;
        else cout << "THIS IS AN INTEREST" << endl;

        if (attr) {
            cout << "Attribue: "<< (char*) _attr << " Length: "<< _attrLen << endl;
        }
        if (val) {
            cout << "Value: " << (char*) _val << " Length: "<< _valLen << endl;
        }
        if (extra){
            if (!_isPublisher){
                cout << "Interest Num: " << _interestNum << endl;
                cout << "Matched: " << _match << endl;
            }
            cout << "NOT: " << _not << endl;
        }
        if (attrHash) {
            cout << "Attribute Hash:" << endl;
            for (int i = 0; i < HASH_SIZE; i++){
                printf("0x%x ", _attrHash[i]);
            }
            cout << endl;
        }
        if (valHash) {
            cout << "Value Hash:" << endl;
            for (int i = 0; i < HASH_SIZE; i++){
                printf("0x%x ", _valHash[i]);
            }
            cout << endl;
        }
        cout << "       --------------------       " << endl;
    }
}

void Tag::printGateVariables(){
    string type;
    if (_gateType == AND) type = "AND"; else type = "OR";
    cout << "THIS IS AN " << type << " GATE" << endl;
    cout << "------------------------------------" << endl;
    _left->printTag(true,true,false,false);
    _right->printTag(true,true,false,false);
    cout << "------------------------------------" << endl;
}