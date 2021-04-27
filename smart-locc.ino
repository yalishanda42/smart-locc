#include <Bounce2.h>
#include "StateManager.hpp"

/// Make sure the button pin has an internal pullup resistor
#define BUTTON_PIN D6
Bounce2::Button button;

StateManager stateManager;
DeviceState lastState = INITIAL;

void setup() {
    Serial.begin(115200);
    Serial.println("Booting up...");

    // Just for EEPROM debug purposes:
    Serial.print((char)EEPROM.read(0));
    Serial.print((char)EEPROM.read(1));
    Serial.print((char)EEPROM.read(2));
    Serial.print(" ");
    Serial.println((int)EEPROM.read(3));

    // Button setup
    button.attach(BUTTON_PIN, INPUT_PULLUP);
    button.interval(50); // debounce in milliseconds
    button.setPressedState(HIGH);

    // TODO
    // ...
    //

    stateManager.setupDidFinish();
    Serial.println("Booted up.");
}

void loop() {
    stateManager.setCurrentTime(millis());
    const DeviceState currentState = stateManager.getState();
    if (currentState != lastState) {
        lastState = currentState;
        Serial.print("STATE -> ");
        Serial.println(currentState);

        // TODO: update lock state, display info, etc
        // ...
        //

    }

    button.update();
    if (button.pressed() && currentState == DeviceState::IDLE) {
        Serial.println("BUTTON PRESSED");
        stateManager.beginAddingNewKey();
        return;
    }

    // TODO: detect authorization attempt
    // ...
    //
}
