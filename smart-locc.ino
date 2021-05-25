#include <Bounce2.h>
#include <WiFiManager.h>
#include <PubSubClient.h>
#include <Wire.h>
#include <Sodaq_SHT2x.h>
#include "StateManager.hpp"
#include "Config.h"
#include "Lock.hpp"
#include "Display.hpp"
#include "DisplayConfig.hpp"
#include "RFIDReader.hpp"

#define TIME_UNTIL_TEMP_MEASURE 5000
/// Make sure the button pin has an internal pullup resistor
#if defined(ESP8266)
/*
 * Temp/Humidity SENSOR PINS - VIN, GND, D2 - SDA, D1 - SCL
 * DISPLAY PINS - VIN, GND, D2 - SDA, D1 - SCL
 * LOCK PIN - D0
 */
#define LOCK_PIN D0
#define READER_SDA D4
#define RST_PIN D3
#define SDA_PIN D2
#define SCL_PIN D1
#define BUTTON_PIN D8
#elif defined(ESP32)
#define BUTTON_PIN 4
#define LOCK_PIN 0
#define READER_SDA 5
#define RST_PIN 6
#define SDA_PIN 2
#define SCL_PIN 1
#endif

Display display(0x27, 16, 2);
Lock lock(LOCK_PIN);
RFIDReader reader{READER_SDA, RST_PIN};

unsigned long lastTemperatureMeasure = 0;

Bounce2::Button button;

StateManager stateManager;
DeviceState lastState = INITIAL;

WiFiManager wm;
WiFiClient espClient;
PubSubClient client(MQTT_SERVER, MQTT_PORT, espClient);

void setup()
{
    Serial.begin(115200);
    Serial.println("Booting up...");

    // WiFi connectivity setup
    Serial.print("Connecting to ");
    wm.autoConnect();

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

    // Lock and Display setup
    lock.init();
    display.init();

    // Temperature and Humidity Sensor
    Wire.begin(SDA_PIN, SCL_PIN);

    // Reader
    reader.init();
    
    stateManager.setupDidFinish();
    Serial.println("Booted up.");

    //Initial Display Info
    DisplayConfig::displayTemperatureAndHumidity(display, SHT2x.GetTemperature(), SHT2x.GetHumidity());
}

void loop()
{
  
    if (!client.connected())
    {
        Serial.print("Reconnecting to server...");
        bool connected = client.connect(CLIENT_ID, USER_TOKEN, PASS);
        Serial.println(connected ? "success" : "failure");
    }
    else
    {
        client.loop();
    }
  
    stateManager.setCurrentTime(millis());
    const DeviceState currentState = stateManager.getState();

    if (currentState == DeviceState::IDLE && stateManager.getCurrentTime() - lastTemperatureMeasure > TIME_UNTIL_TEMP_MEASURE) {
        DisplayConfig::displayTemperatureAndHumidity(display, SHT2x.GetTemperature(), SHT2x.GetHumidity());
        lastTemperatureMeasure = stateManager.getCurrentTime();
    }
    
    if (currentState != lastState)
    {
        lastState = currentState;
        Serial.print("STATE -> ");
        Serial.println(currentState);

        switch(currentState) {
            case DeviceState::IDLE:
                DisplayConfig::displayTemperatureAndHumidity(display, SHT2x.GetTemperature(), SHT2x.GetHumidity());
                lock.lock();
                break;
            case DeviceState::AUTHORIZED:
                DisplayConfig::displayDoorUnlockedMessage(display);
                lock.unlock();
                break;
            case DeviceState::WAITING_ADMIN_AUTH:
                DisplayConfig::displayAdminKeyMessage(display);
                break;
            case DeviceState::WAITING_NEW_KEY_AUTH:
                DisplayConfig::displayNewKeyAuthMessage(display);
                break;
            case DeviceState::NEW_KEY_AUTH_SUCCESS:
                DisplayConfig::displayKeyAddedMessage(display);         
                break;
            case DeviceState::AUTH_FAILURE:
                DisplayConfig::displayNotAuthorizedMessage(display);
                break;
        }
        
        if (currentState == DeviceState::AUTHORIZED || currentState == DeviceState::AUTH_FAILURE)
        {
            String data = "{\"" + String(currentState == DeviceState::AUTHORIZED ? VARIABLE_LABEL_SUCCESSFUL : VARIABLE_LABEL_UNSUCCESSFUL) + "\":{\"value\":1}}";
            client.publish(TOPIC, data.c_str());
        }
    }

    button.update();
    if (button.pressed() && currentState == DeviceState::IDLE)
    {
        Serial.println("BUTTON PRESSED");
        stateManager.beginAddingNewKey();
        return;
    }

    bool wasPICCRead = reader.tryReadingPICC();
    if (wasPICCRead) {
        stateManager.authorize(reader.getUID());
    }
}
