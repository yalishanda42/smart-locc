#include "RFIDReader.hpp"
#include <SPI.h>

RFIDReader::RFIDReader(int sdaPin, int resetPin) : rfid(sdaPin, resetPin) {}

void RFIDReader::init() {
	SPI.begin();
	this->rfid.PCD_Init();
}

bool RFIDReader::tryReadingPICC() {

	//return false if no new card present on the reader
	if (!this->rfid.PICC_IsNewCardPresent()) {
		return false;
	}

	//return false if the NUID was not read
	if (!this->rfid.PICC_ReadCardSerial()) {
		return false;
	}

	//Halt current PICC(chip/card)
	this->rfid.PICC_HaltA();

	return true;
}

KeyID RFIDReader::getUID() const {
  unsigned char bytes[KEY_SIZE_BYTES] = {0};
  
  for (unsigned char i = 0; i < this->rfid.uid.size; i++) {
      bytes[i] = this->rfid.uid.uidByte[i];
  }
  
	return KeyID{bytes};
}
