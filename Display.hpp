#ifndef __DISPLAY__HPP__
#define __DISPLAY__HPP__

#include "LiquidCrystal_I2C.h"

class Display
{
	private:
		LiquidCrystal_I2C lcd;
		int columns;
		int lines;
		int currentLine;
		int currentColumn;

	public:
		Display(const unsigned int& address, int columns, int lines);
		Display(const Display&) = delete;
		Display& operator=(const Display&) = delete;

		void init();
		void clear();
		void print(const char* str, int line = 0, int column = 0);
		void append(const char* str);
};

#endif
