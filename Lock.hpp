#ifndef __LOCK_HPP__
#define __LOCK_HPP__

class Lock {
	private:
		bool locked;
		int pin;
	public:
		Lock(int pin);
		Lock(const Lock&) = delete;
		Lock& operator=(const Lock&) = delete;

		void init();
		void unlock(int timeBeforeLock = 0);
		void lock();
		bool isLocked() const;
};

#endif
