// Uncomment the following line if you are using NodeMCU
//#include "nodemcu.h"

//#include <ESP8266WiFi.h>

#include "StateManager.hpp"

StateManager stateManager;

void setup() {
    Serial.begin(115200);
    Serial.println("Booting up...");

    // Just for EEPROM debug purposes:
    Serial.print((char)EEPROM.read(0));
    Serial.print((char)EEPROM.read(1));
    Serial.print((char)EEPROM.read(2));
    Serial.print(" ");
    Serial.println((int)EEPROM.read(3));

    // TODO
    // ...
    //

    stateManager.setupDidFinish();
    Serial.println("Booted up.");
}

void loop() {
    stateManager.setCurrentTime(millis());
    // TODO
    // ...
    //
}
