#include "const.h"
#include "setting.h"
#include <SPI.h>
#include <EEPROM.h>

int Setting::operator++() {
	if (value == upperBound) return 0;
	return ++value;
}

int Setting::operator--() {
	if (value == lowerBound) return 0;
	return --value;
}

int Setting::get() {
	return value;
}

int Setting::read() {
	return EEPROM.read(address);
}

void Setting::write() {
	EEPROM.write(address, value);
}

void Setting::apply() {
	digitalWrite(PIN_DIGIPOT, LOW);
  SPI.transfer(address);
  SPI.transfer(value);
  digitalWrite(PIN_DIGIPOT, HIGH);
}
