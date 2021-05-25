#include "DisplayConfig.hpp"

void DisplayConfig::displayTemperatureAndHumidity(Display& display, int temperature, int humidity) {
	display.clear();
	display.print((String{"Temperature: " } + temperature + "C").c_str());
	display.print((String{ "Humidity: " } + humidity + "%").c_str(), 1);
}

void DisplayConfig::displayAdminKeyMessage(Display& display) {
	display.clear();
	display.print("Please authorize");
	display.print("admin key", 1);
}

void DisplayConfig::displayNewKeyAuthMessage(Display& display) {
	display.clear();
	display.print("Please authorize");
	display.print("new key", 1);
}

void DisplayConfig::displayKeyAddedMessage(Display& display) {
	display.clear();
	display.print("Welcome! You are");
	display.print("now authorized.", 1);
}

void DisplayConfig::displayNotAuthorizedMessage(Display& display) {
	display.clear();
	display.print("Authorization");
	display.print("failed", 1);
}

void DisplayConfig::displayDoorUnlockedMessage(Display& display) {
	display.clear();
	display.print("Door unlocked!");
}
