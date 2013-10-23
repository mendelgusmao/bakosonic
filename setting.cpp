#include "const.h"
#include "setting.h"
#include <Arduino.h>
#include <SPI.h>
#include <EEPROM.h>

Setting::Setting(const int address, const int offset, const int lowerBound, const int upperBound) :
_address(address),
_offset(offset),
_value(lowerBound),
_lowerBound(lowerBound),
_upperBound(upperBound)
{
}

int Setting::operator++() {
  if (_value == _upperBound) return 0;
  apply();
  return ++_value;
}

int Setting::operator--() {
  if (_value == _lowerBound) return 0;
  apply();
  return --_value;
}

int Setting::get() {
  return _value;
}

void Setting::set(const int value) {
  _value = value;
  apply();
}

int Setting::read() {
  return EEPROM.read(_address + _offset);
}

void Setting::write() {
  EEPROM.write(_address + _offset, _value);
}

void Setting::apply() {
  digitalWrite(PIN_DIGIPOT_CS, LOW);
  SPI.transfer(_address + _offset);
  SPI.transfer(_value);
  digitalWrite(PIN_DIGIPOT_CS, HIGH);
}

void Setting::setOffset(const int offset) {
  _offset = offset;
}