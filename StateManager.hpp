#ifndef __STATE_MANAGER__HPP__
#define __STATE_MANAGER__HPP__

enum DeviceState {
    INITIAL,

    IDLE,

    AUTHORIZED,
    AUTH_FAILURE,

    WAITING_ADMIN_AUTH,
    WAITING_NEW_KEY_AUTH,
    NEW_KEY_AUTH_SUCCESS,
};

/// Should hold milliseconds
typedef unsigned long DeviceTime;

class StateManager
{
public:
    StateManager();

    /// Call this at the beginning of every loop
    void setCurrentTime(DeviceTime);

    /// Current device state (TODO: do we need a getter?)
    DeviceState getState() const;

    /// Current state display message
    const char* getStateMessage() const;

    /// Locked or unlocked
    bool isLocked() const;

    /* Actions */

    void setupDidFinish();

    // TODO
    // void authorize(byte[10]);

private:
    DeviceState state;
    DeviceTime lastStateUpdateTime;
    DeviceTime currentTime;

    void setState(DeviceState);

    DeviceTime getTimeoutForCurrentState();
};

#endif