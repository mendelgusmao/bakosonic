#include "const.h"
#include "setting.h"
#include "channel_setting.h"

#ifndef TV_H
#define TV_H

class TV {
private:
  int _pinRelay;
  bool _on;
  int _screen;

public:
  ChannelSetting channel;
  Setting volume;
  Setting brightness;
  Setting contrast;
  Setting vertical;

  TV(const int pinRelay) : 
  _pinRelay(pinRelay),
  _on(false),
  _screen(SCREEN_MAIN),
  channel(ADDRESS_CHANNEL, 2, CHAN_FLOOR, CHAN_CEIL),
  volume(ADDRESS_VOLUME, 0, 0, 255),
  brightness(ADDRESS_BRIGHTNESS, 0, 0, 255),
  contrast(ADDRESS_CONTRAST, 0, 0, 255),
  vertical(ADDRESS_VERTICAL, 0, 0, 255)
  {
  }

  void toggle();
  bool isOn();

};

#endif // TV_H


