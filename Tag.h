#ifndef TAG_H
#define TAG_H

using namespace std;

#include <stdint.h>

#define INPUT_SIZE 20
#define HASH_SIZE 32

class Tag
{
  public:
    //Hash Values
    void genHash(uint8_t *key);
    void genSubHash(uint8_t *key, string &r);
    bool compareRHash(Tag interest);
    uint8_t getAttrHash(int);
    uint8_t getValHash(int);
    uint8_t getRHash(int);
    string getR();

    //Search Functionality
    bool operator==(const Tag &other);
    void matched();
    bool isMatch();
    bool isReal();

    //Constructor Methods
    Tag(const char *, const char *, bool = true, bool = true, char = '=');
    Tag(uint8_t *, uint8_t *, bool = true,  uint8_t * = {}, string = "");
    Tag();
    //Deconstructor
    ~Tag();
    //Copy Constructor and Assignment
    Tag(const Tag &other);
    Tag &operator=(const Tag &other);
    //Move Constructor and Assignment
    Tag(Tag &&other);
    Tag &operator=(Tag &&other);

    //Debugging
    void print(bool = true, bool = true, bool = true, bool = true, bool = true);

  private:
    //Variables
    //->For Tags/Interests
    char _attr[INPUT_SIZE];
    char _val[INPUT_SIZE];
    uint8_t _attrHash[HASH_SIZE];
    uint8_t _valHash[HASH_SIZE];
    uint8_t _rHash[HASH_SIZE];
    string _r = "";
    int _attrLen;
    int _valLen;
    bool _isPublisher = true;
    char _opr;
    bool _match = false;
    bool _real;

};

#endif
