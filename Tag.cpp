using namespace std;
#include <string.h>
#include <iostream>

#include "Tag.h"
#include "hash.h"

// == Operator
bool Tag::operator==(const Tag &other)
{
    bool attrBool = memcmp(_attrHash, other._attrHash, HASH_SIZE) == 0;
    bool valBool = memcmp(_valHash, other._valHash, HASH_SIZE) == 0;
    return attrBool && valBool;
}

//Matched
void Tag::matched()
{
    _match = true;
}

bool Tag::isMatch()
{
    return _match;
}

/*  Generates a hash for both the attribute and val and then stores it in the 
*   Tag structure.
*   @param tag - a Tag object
*   @param key - private key
*/
void Tag::genHash(uint8_t *key)
{
    KeyedHash(key, HASH_SIZE, (uint8_t *)_attr, _attrLen, _attrHash, HASH_SIZE);
    KeyedHash(key, HASH_SIZE, (uint8_t *)_val, _valLen, _valHash, HASH_SIZE);
}

/* ----------- CONTRUCTORS ----------- */

//Tag and Interest Constructor
Tag::Tag(const char *newAttr, const char *newVal, bool isPublisher, char opr)
{
    strcpy(_attr, newAttr);
    strcpy(_val, newVal);
    _attrLen = strlen(newAttr);
    _valLen = strlen(newVal);
    _isPublisher = isPublisher;
    _opr = opr;
}

//Empty Constructor
Tag::Tag(){};

//Deconstructor
Tag::~Tag(){};

//Copy Constructor
Tag::Tag(const Tag &other)
{
    //Copy Attributes and Values
    memcpy(_attr, other._attr, INPUT_SIZE);
    memcpy(_val, other._val, INPUT_SIZE);

    //Copy Hashes of attributes and values
    memcpy(_attrHash, other._attrHash, HASH_SIZE);
    memcpy(_valHash, other._valHash, HASH_SIZE);

    //Copy Attributes and Value lengths
    _attrLen = other._attrLen;
    _valLen = other._valLen;

    //Remaining stuff copied
    _isPublisher = other._isPublisher;
    _opr = other._opr;
    _match = other._match;
}

//Copy Assignment
Tag &Tag::operator=(const Tag &other)
{
    //Delete Old elements
    memset(_attr, 0, INPUT_SIZE);
    memset(_val, 0, INPUT_SIZE);
    memset(_attrHash, 0, HASH_SIZE);
    memset(_valHash, 0, HASH_SIZE);

    //Copy Attributes and Values
    memcpy(_attr, other._attr, INPUT_SIZE);
    memcpy(_val, other._val, INPUT_SIZE);

    //Copy Hashes of attributes and values
    memcpy(_attrHash, other._attrHash, HASH_SIZE);
    memcpy(_valHash, other._valHash, HASH_SIZE);

    //Copy Attributes and Value lengths
    _attrLen = other._attrLen;
    _valLen = other._valLen;

    //Remaining stuff copied
    _isPublisher = other._isPublisher;
    _opr = other._opr;
    _match = other._match;
}

//Move Contructor
Tag::Tag(Tag &&other)
{
    //Move Attributes and Values
    memcpy(_attr, other._attr, INPUT_SIZE);
    memcpy(_val, other._val, INPUT_SIZE);
    memset(other._attr, 0, INPUT_SIZE);
    memset(other._val, 0, INPUT_SIZE);

    //Copy Hashes of attributes and values
    memcpy(_attrHash, other._attrHash, HASH_SIZE);
    memcpy(_valHash, other._valHash, HASH_SIZE);
    memset(other._attrHash, 0, HASH_SIZE);
    memset(other._valHash, 0, HASH_SIZE);

    //Copy Attributes and Value lengths
    _attrLen = other._attrLen;
    _valLen = other._valLen;
    other._attrLen = 0;
    other._valLen = 0;

    //Remaining stuff copied
    _isPublisher = other._isPublisher;
    _opr = other._opr;
    _match = other._match;

    other._isPublisher = 0;
    other._opr = 0;
    other._match = 0;
}

//Move Assignment
Tag &Tag::operator=(Tag &&other)
{
    //Delete old elements
    memset(_attr, 0, INPUT_SIZE);
    memset(_val, 0, INPUT_SIZE);
    memset(_attrHash, 0, HASH_SIZE);
    memset(_valHash, 0, HASH_SIZE);

    //Move Attributes and Values
    memcpy(_attr, other._attr, INPUT_SIZE);
    memcpy(_val, other._val, INPUT_SIZE);
    memset(other._attr, 0, INPUT_SIZE);
    memset(other._val, 0, INPUT_SIZE);

    //Copy Hashes of attributes and values
    memcpy(_attrHash, other._attrHash, HASH_SIZE);
    memcpy(_valHash, other._valHash, HASH_SIZE);
    memset(other._attrHash, 0, HASH_SIZE);
    memset(other._valHash, 0, HASH_SIZE);

    //Copy Attributes and Value lengths
    _attrLen = other._attrLen;
    _valLen = other._valLen;
    other._attrLen = 0;
    other._valLen = 0;

    //Remaining stuff copied
    _isPublisher = other._isPublisher;
    _opr = other._opr;
    _match = other._match;

    other._isPublisher = 0;
    other._opr = 0;
    other._match = 0;
}

/* ----------- DEBUG FUNCTIONS ----------- */

/*Prints out all important tag information
*/
void Tag::print(bool attr, bool val, bool attrHash, bool valHash, bool extra)
{
    cout << "       --------------------       " << endl;
    if (_isPublisher)
        cout << "THIS IS A TAG" << endl;
    else
        cout << "THIS IS AN INTEREST" << endl;

    if (attr)
    {
        cout << "Attribue: " << (char *)_attr << " Length: " << _attrLen << endl;
    }
    if (val)
    {
        cout << "Value: " << (char *)_val << " Length: " << _valLen << endl;
    }
    if (extra)
    {
        if (!_isPublisher)
        {
            cout << "Matched: " << _match << endl;
        }
    }
    if (attrHash)
    {
        cout << "Attribute Hash:" << endl;
        for (int i = 0; i < HASH_SIZE; i++)
        {
            printf("0x%x ", _attrHash[i]);
        }
        cout << endl;
    }
    if (valHash)
    {
        cout << "Value Hash:" << endl;
        for (int i = 0; i < HASH_SIZE; i++)
        {
            printf("0x%x ", _valHash[i]);
        }
        cout << endl;
    }
    cout << "       --------------------       " << endl;
}
