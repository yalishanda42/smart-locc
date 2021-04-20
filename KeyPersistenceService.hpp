#ifndef __KEY_PERSISTENCE_SERVICE__HPP__
#define __KEY_PERSISTENCE_SERVICE__HPP__

#include <EEPROM.h>

#define KEY_SIZE_BYTES 12
struct KeyID {
    unsigned char bytes[KEY_SIZE_BYTES];

    KeyID(unsigned char[KEY_SIZE_BYTES]);
    bool operator==(const KeyID &) const;
};

class KeyPersistenceService
{
    static const int INITGUARD_LENGTH = 3;
    static const char INITGUARD[INITGUARD_LENGTH + 1];

    unsigned char numberOfKeys;

public:
    KeyPersistenceService();

    bool keyIsAuthorized(KeyID) const;
    bool keyIsAdmin(KeyID) const;
    bool addKey(KeyID) const;
};

#endif