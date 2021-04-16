// Uncomment the following line if you are using NodeMCU
//#include "nodemcu.h"

//#include <ESP8266WiFi.h>

#include "StateManager.hpp"

StateManager stateManager;

void setup() {
    Serial.begin(115200);
    Serial.println("Booting up...");
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