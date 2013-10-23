#include "const.h"
#include "channel_setting.h"
#include <SPI.h>
#include <EEPROM.h>

void ChannelSetting::readAll() {
  for (int index = CHAN_FLOOR + EEPROM_OFFSET; index <= CHAN_CEIL + EEPROM_OFFSET; index++) {
    ChannelSetting::channels[index] = EEPROM.read(index);
  }
}

void ChannelSetting::apply() {
  int position = ChannelSetting::channels[_value];

  digitalWrite(PIN_DIGIPOT_CS, LOW);
  SPI.transfer(ADDRESS_CHANNEL);
  SPI.transfer(position);
  digitalWrite(PIN_DIGIPOT_CS, HIGH);
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
