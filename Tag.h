#ifndef TAG_H
#define TAG_H

using namespace std;

#include <stdint.h>
#include <array>

#define INPUT_SIZE 20
#define HASH_SIZE 32

class Tag
{
  public:
    //Hash Values
    void genHash(uint8_t *key);
    void genSubHash(uint8_t *key, string &r);
    bool compareRHash(Tag interest);
    uint8_t getAttrHash(int i) {
        return _attrHash[i];
    }
    uint8_t getValHash(int i) {
        return _valHash[i];
    }

    uint8_t getRHash(int i) {
        return _rHash[i];
    }

    string getR() {
        return _r;
    }

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

    //Public Variables
    string _attrHashString ="";

  private:
    //Variables
    //->For Tags/Interests
    char _attr[INPUT_SIZE];
    char _val[INPUT_SIZE];
    uint8_t _valHash[HASH_SIZE];
    uint8_t _rHash[HASH_SIZE];
    uint8_t _attrHash[HASH_SIZE];
    string _r = "";
    int _attrLen;
    int _valLen;
    bool _isPublisher = true;
    char _opr;
    bool _match = false;
    bool _real;

};

#endif
