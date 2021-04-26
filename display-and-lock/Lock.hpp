#ifndef LOCK_HPP
#define LOCK_HPP

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