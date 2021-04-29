#include "Display.hpp"
#include <string.h>
#include <SoftwareSerial.h>

Display::Display(const unsigned int& address, int columns, int lines) :
	lcd{ address, columns, lines },
	columns(columns),
	lines(lines),
	currentLine(0),
	currentColumn(0) {}

void Display::init() {
	this->lcd.init();
	this->lcd.backlight();
}

void Display::clear() {
	this->lcd.clear();
	this->currentLine = 0;
	this->currentColumn = 0;
}

void Display::print(const char* str, int line, int column) {
	int currStrLen = strlen(str);
	if (currStrLen + column > this->columns) {
		Serial.println(String{ "String " } + "\"" + str + "\"" + " will be concatenated on printing");
	}
	this->currentColumn = currStrLen;
	this->currentLine = line;
	this->lcd.setCursor(column, line);
	this->lcd.print(str);
}

void Display::append(const char* str) {
	int currStrLen = strlen(str);
	if (currStrLen + this->currentColumn > this->columns) {
		Serial.println(String{ "String " } + "\"" + str + "\"" + " will be concatenated on appending");
	}
	this->currentColumn += currStrLen;
	this->lcd.print(str);
}
