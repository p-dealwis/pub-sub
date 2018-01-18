#ifndef TAG_H
#define TAG_H

#include <stdint.h>

#define INPUT_SIZE 20
#define HASH_SIZE 32

#define AND 0
#define OR 1

class Tag {
public:
    //Search Functionality
    bool operator==(const Tag& other);
    void matched();
    bool isMatch();
    
    //TODO: DELETE IF NOT NEEDED
    bool checkValue(Tag* otherLeftTag, Tag* otherRightTag);

    //Constructor Methods
    Tag(const char*, const char*, uint8_t*, bool = true, char = '=');
    Tag(int, Tag*, bool, Tag*, bool);
    Tag(int, Tag*, Tag*, bool);
    Tag(int, Tag*, Tag*);
    Tag();
    //Deconstructor
    ~Tag();
    //Copy Constructor and Assignment
    Tag(const Tag& other);
    Tag& operator=(const Tag& other);
    //Move Constructor and Assignment
    Tag(Tag&& other);
    Tag& operator=(Tag&& other);

    //Debugging
    void print(bool = true, bool = true, bool = true, bool = true, bool = true);

private:
    //Variables
    //->For Tags/Interests
    char _attr[INPUT_SIZE];
    char _val[INPUT_SIZE];
    uint8_t _attrHash [HASH_SIZE];
    uint8_t _valHash [HASH_SIZE];
    int _attrLen;
    int _valLen;
    bool _isPublisher = true;
    char _opr;
    bool _match = false;

    //Tag encryption
    void genHash(uint8_t* key);
};

#endif
