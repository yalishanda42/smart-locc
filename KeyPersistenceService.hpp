#ifndef __KEY_PERSISTENCE_SERVICE__HPP__
#define __KEY_PERSISTENCE_SERVICE__HPP__

#include <EEPROM.h>
#include "KeyID.hpp"

class KeyPersistenceService
{
    static const unsigned int EEPROM_LENGTH = 512;

    static const unsigned int INITGUARD_LENGTH = 3;
    static const char INITGUARD[INITGUARD_LENGTH + 1];

    static const unsigned int NUMBER_OF_ADMIN_KEYS = 2;
    static const unsigned char ADMIN_KEYS[NUMBER_OF_ADMIN_KEYS][KEY_SIZE_BYTES];

    unsigned char numberOfKeys;

public:
    KeyPersistenceService();

    bool keyIsAuthorized(const KeyID&) const;
    bool keyIsAdmin(const KeyID&) const;
    bool addKey(const KeyID&);

private:  // Helpers
    bool keyExistsInFirstNEntries(const KeyID& key, unsigned int N) const;
};

#endif
