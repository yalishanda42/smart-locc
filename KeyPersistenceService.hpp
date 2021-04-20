#ifndef __KEY_PERSISTENCE_SERVICE__HPP__
#define __KEY_PERSISTENCE_SERVICE__HPP__

#define KEY_SIZE_BYTES 12
typedef unsigned char KeyID[KEY_SIZE_BYTES];

class KeyPersistenceService
{
public:
    bool keyIsAuthorized(KeyID) const;
    bool keyIsAdmin(KeyID) const;
    bool addKey(KeyID) const;
};

#endif