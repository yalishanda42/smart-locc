#include "KeyPersistenceService.hpp"

const char KeyPersistenceService::INITGUARD[INITGUARD_LENGTH + 1] = "key";

const unsigned char KeyPersistenceService::ADMIN_KEYS[NUMBER_OF_ADMIN_KEYS][KEY_SIZE_BYTES] = {
    {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
    {0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC},
};

KeyPersistenceService::KeyPersistenceService() : numberOfKeys(0) {
    EEPROM.begin(EEPROM_LENGTH);

    // To prevent reading and trusting uninitialized data
    // we should ensure that the first INITGUARD_LENGTH number of
    // bytes of EEPROM are always the same and set by our program.
    //
    // The one byte after the password should hold the number of keys persisted.

    bool isInitializedProperly = true;
    for (unsigned int i = 0; i < INITGUARD_LENGTH; i++) {
        if (EEPROM.read(i) != INITGUARD[i]) {
            isInitializedProperly = false;
            break;
        }
    }

    if (!isInitializedProperly) {
        for (unsigned int i = 0; i < INITGUARD_LENGTH; i++) {
            EEPROM.write(i, INITGUARD[i]);
        }
        EEPROM.write(INITGUARD_LENGTH, numberOfKeys);

        for (unsigned int i = 0; i < NUMBER_OF_ADMIN_KEYS; i++) {
            addKey(ADMIN_KEYS[i]);
        }

        // no need to say `EEPROM.commit()` here because `addKey()` does it

    } else {
        numberOfKeys = EEPROM.read(INITGUARD_LENGTH);
    }
}

bool KeyPersistenceService::keyIsAuthorized(const KeyID& key) const {
    return keyExistsInFirstNEntries(key, numberOfKeys);
}

bool KeyPersistenceService::keyIsAdmin(const KeyID& key) const {
    return keyExistsInFirstNEntries(key, NUMBER_OF_ADMIN_KEYS);
}

bool KeyPersistenceService::addKey(const KeyID& key) {
    unsigned int usedEEPROMSize = INITGUARD_LENGTH + 1 + (numberOfKeys * KEY_SIZE_BYTES);
    if (EEPROM_LENGTH - usedEEPROMSize < KEY_SIZE_BYTES) {
        // No enough space available for a new key!
        return false;
    }

    EEPROM.put(usedEEPROMSize, key);
    EEPROM.write(INITGUARD_LENGTH, numberOfKeys + 1);

    bool success = EEPROM.commit();
    if (success) numberOfKeys++;
    return success;
}

bool KeyPersistenceService::keyExistsInFirstNEntries(const KeyID& key, unsigned int N) const {
    unsigned int addr = INITGUARD_LENGTH + 1;
    KeyID currentKey = {0};

    for (unsigned int i = 0; i < N; i++) {
        EEPROM.get(addr, currentKey);

        if (currentKey == key) {
            return true;
        }

        addr += KEY_SIZE_BYTES;
    }

    return false;
}
