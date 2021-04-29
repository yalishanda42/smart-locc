#ifndef KEYID_HPP
#define KEYID_HPP

#define KEY_SIZE_BYTES 12

struct KeyID {
    unsigned char bytes[KEY_SIZE_BYTES];

    KeyID(const unsigned char[KEY_SIZE_BYTES]);
    bool operator==(const KeyID&) const;
};

#endif
