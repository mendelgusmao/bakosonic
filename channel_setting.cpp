#include "const.h"
#include "channel_setting.h"
#include <SPI.h>
#include <EEPROM.h>

void ChannelSetting::readAll() {
  for (int index = CHAN_FLOOR + EEPROM_OFFSET; index <= CHAN_CEIL + EEPROM_OFFSET; index++) {
    ChannelSetting::channels[index] = EEPROM.read(index);
  }
}

int ChannelSetting::operator++() {
  _value = _value == _upperBound ? _lowerBound : _value + 1;

  apply();
  return _value;
}

int ChannelSetting::operator--() {
  _value = _value == _lowerBound ? _upperBound : _value - 1;

  apply();
  return _value;
}

void ChannelSetting::set(const int value) {
  _value = value;
  apply();
}

void ChannelSetting::apply() {
  tuning.set(ChannelSetting::channels[get()]);
  tuning.apply();
}

void ChannelSetting::write() {
  EEPROM.write(_address + _offset, _value);

  tuning.setOffset(get());
  tuning.set(ChannelSetting::channels[get()]);
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
