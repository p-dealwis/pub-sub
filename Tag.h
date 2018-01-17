#ifndef TAG_H
#define TAG_H

#include <stdint.h>

#define INPUT_SIZE 20
#define HASH_SIZE 32

class Tag {
public:
    Tag(const char*, const char*, uint8_t*, bool = true, char = '=');
    Tag();
    //Deconstructor
    ~Tag();
    //Copy Constructor and Assignment
    Tag(const Tag& other);
    Tag& operator=(const Tag& other);
    //Move Constructor and Assignment
    Tag(Tag&& other);
    Tag& operator=(Tag&& other);
    
    void printTag(bool = true, bool = true, bool = true, bool = true);

private:
    char _attr[INPUT_SIZE];
    char _val[INPUT_SIZE];
    uint8_t _attrHash [HASH_SIZE];
    uint8_t _valHash [HASH_SIZE];
    int _attrLen;
    int _valLen;
    bool _isPublisher;
    char _opr;
    //Tag encryption
    void genHash(uint8_t* key);
};

#endif
