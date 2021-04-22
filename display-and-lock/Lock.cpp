#include "Lock.hpp"
#include <Arduino.h>

Lock::Lock(int _pin) : pin(_pin), locked(false) {}

void Lock::init() {
	pinMode(this->pin, OUTPUT);
	digitalWrite(this->pin, HIGH);
	this->locked = true;
}

void Lock::unlock(int timeBeforeLock) {
	digitalWrite(this->pin, LOW);
	this->locked = false;
	if (timeBeforeLock != 0) {
		delay(timeBeforeLock);
		digitalWrite(this->pin, HIGH);
		this->locked = true;
	}
} 

bool Lock::isLocked() const{
	return this->locked;
}