#include "KeyID.hpp"

KeyID::KeyID(const unsigned char bytes[KEY_SIZE_BYTES]) {
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
