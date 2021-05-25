#ifndef __DISPLAYCONFIG__HPP__
#define __DISPLAYCONFIG__HPP__

#include "Display.hpp"

class DisplayConfig {
	public:
		static void displayTemperatureAndHumidity(Display& display, int temperature, int humidity);
		static void displayAdminKeyMessage(Display& display);
		static void displayNewKeyAuthMessage(Display& display);
		static void displayKeyAddedMessage(Display& display);
		static void displayDoorUnlockedMessage(Display& display);
		static void displayNotAuthorizedMessage(Display& display);
		static void displayDoorUnlockedMessage(Display& display);
};

#endif
