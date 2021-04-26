#include "Lock.hpp"
#include "Display.hpp"
#include "DisplayConfig.hpp"
#include <stdlib.h>

/*
 * DISPLAY PINS - VIN, GND, D2- SDA, D1 - SCL
 * LOCK PIN - D0
 */
Display current(0x27, 16, 2);
Lock lock(D0);

void setup()
{
  lock.init();
  current.init();
}

void loop(){
  DisplayConfig::displayTemperatureAndHumidity(current, rand() % 30, rand() % 50);
  delay(2500);
  DisplayConfig::displayAdminKeyMessage(current);
  delay(2500);
  DisplayConfig::displayNewKeyAuthMessage(current);
  delay(2500);
  DisplayConfig::displayKeyAddedMessage(current);
  delay(2500);
  DisplayConfig::displayDoorUnlockedMessage(current);
  lock.unlock();
  delay(2500);
  DisplayConfig::displayDoorLockedMessage(current);
  lock.lock();
  delay(2500);
}
