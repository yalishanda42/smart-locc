#include "KeyPersistenceService.hpp"

KeyID::KeyID(unsigned char bytes[KEY_SIZE_BYTES]) {
    for (unsigned int i = 0; i < KEY_SIZE_BYTES; i++) {
        this->bytes[i] = bytes[i];
    }
}

bool KeyID::operator==(const KeyID& rhs) const {
    for (unsigned int i = 0; i < KEY_SIZE_BYTES; i++) {
        if (bytes[i] != rhs.bytes[i]) {
            return false;
        }
    }
    return true;
}

const char KeyPersistenceService::INITGUARD[INITGUARD_LENGTH + 1] = "key";

KeyPersistenceService::KeyPersistenceService() : numberOfKeys(0) {
    EEPROM.begin(EEPROM.length());

    // To prevent reading and trusting uninitialized data
    // we should ensure that the first 3 bytes of EEPROM are always
    // the same and set by our program.
    //
    // The byte after the password should hold the number of keys persisted.

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
    } else {
        numberOfKeys = EEPROM.read(INITGUARD_LENGTH);
    }
}

bool KeyPersistenceService::keyIsAuthorized(const KeyID& key) const {
    unsigned int addr = INITGUARD_LENGTH + 1;
    KeyID currentKey = { 0 };
    for (unsigned int i = 0; i < numberOfKeys; i++) {
        EEPROM.get(addr, currentKey);

        if (currentKey == key) {
            return true;
        }

        addr += KEY_SIZE_BYTES;
    }

    return false;
}

bool KeyPersistenceService::keyIsAdmin(const KeyID&) const {
    // TODO
    return false;
}

bool KeyPersistenceService::addKey(const KeyID&) const {
    // TODO
    return true;
}
