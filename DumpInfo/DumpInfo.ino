#include "RFIDReader.hpp"

/*
 * PINS - D3 - RST, D4 - SDA, D5 - SCK, D6 - MISO, D7 - MOSI
 */

#define SDA_PIN D4
#define RST_PIN D3
 
RFIDReader reader{SDA_PIN, RST_PIN};

void setup() { 
  Serial.begin(9600);
  reader.init();
}
 
void loop() {
  bool wasPICCRead = reader.tryReadingPICC();
  if (wasPICCRead) {
      printHex(reader.getUID().bytes);  
  }
}

void printHex(unsigned char* data) {
  for (byte i = 0; i < KEY_SIZE_BYTES; i++) {
    Serial.print(data[i] < 0x10 ? " 0" : " ");
    Serial.print(data[i], HEX);
  }
  Serial.println();
}
