#include "const.h"
#include "setting.h"
#include <Arduino.h>
#include <SPI.h>
#include <EEPROM.h>

Setting::Setting(const int address, const int defaultValue, const int lowerBound, const int upperBound) :
_address(address),
_value(defaultValue),
_lowerBound(lowerBound),
_upperBound(upperBound)
{
}

int Setting::operator++() {
  if (_value == _upperBound) return 0;
  return ++_value;
}

int Setting::operator--() {
  if (_value == _lowerBound) return 0;
  return --_value;
}

int Setting::get() {
  return _value;
}

int Setting::read() {
  return EEPROM.read(_address);
}

void Setting::write() {
  EEPROM.write(_address, _value);
}

void Setting::apply() {
  digitalWrite(PIN_DIGIPOT_CS, LOW);
  SPI.transfer(_address);
  SPI.transfer(_value);
  digitalWrite(PIN_DIGIPOT_CS, HIGH);
}

