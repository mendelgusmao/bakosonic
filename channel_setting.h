#include "setting.h"

#ifndef CHANNEL_H
#define CHANNEL_H

class ChannelSetting : 
public Setting {
public:
  static int channels[CHAN_CEIL];
  static void readAll();

  Setting tuning;

  ChannelSetting(const int address, const int offset, const int lowerBound, const int upperBound) : 
  Setting(address, offset, lowerBound, upperBound),
  tuning(EEPROM_OFFSET, 0, 0, 255) {
  }

  int operator++();
  int operator--();
  void set(const int value);
  void apply();
  void write();
  const int band();
};

#endif // CHANNEL_H


