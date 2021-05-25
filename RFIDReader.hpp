#ifndef __RFIDREADER__HPP__
#define __RFIDREADER__HPP__

#include <MFRC522.h>
#include "KeyID.hpp"

class RFIDReader {
	private:
		MFRC522 rfid;
	public:
		RFIDReader(int sdaPin, int resetPin);
		RFIDReader(const RFIDReader&) = delete;
		RFIDReader& operator=(const RFIDReader&) = delete;

		void init();
		bool tryReadingPICC();
		KeyID getUID() const;
    
};

#endif
