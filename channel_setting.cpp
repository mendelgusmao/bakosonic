#include "const.h"
#include "channel_setting.h"
#include <SPI.h>
#include <EEPROM.h>

int ChannelSetting::operator++() {
  if (_value == _upperBound) { 
    _value = _lowerBound;
  } else {
    ++_value;
  }

  apply();
  return _value;
}

int ChannelSetting::operator--() {
  if (_value == _lowerBound) { 
    _value = _upperBound;
  } else {
    --_value;
  }

  apply();
  return _value;
}

void ChannelSetting::readAll() {
  for (int index = CHAN_FLOOR + EEPROM_OFFSET; index <= CHAN_CEIL + EEPROM_OFFSET; index++) {
    ChannelSetting::channels[index] = EEPROM.read(index);
  }
}

void ChannelSetting::set(const int value) {
  _value = value;
  apply();
}

void ChannelSetting::apply() {
  digitalWrite(PIN_DIGIPOT_CS, LOW);
  SPI.transfer(_address + _offset);
  SPI.transfer(_value);
  digitalWrite(PIN_DIGIPOT_CS, HIGH);

  tuning.setOffset(get());
  tuning.apply();
}

void ChannelSetting::write() {
  EEPROM.write(_address + _offset, _value);

  tuning.setOffset(get());
  tuning.write();
}

const int ChannelSetting::band() {
  if (_value >= 2 && _value <= 6) {
    return CHAN_BAND_VHF_LOW;
  } 
  else if (_value >= 7 && _value <= 13) {
    return CHAN_BAND_VHF_HIGH;
  }

  return CHAN_BAND_UHF;
}
