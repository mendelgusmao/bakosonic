#include "const.h"
#include "tv.h"
#include "screen.h"
#include "setting.h"
#include "channel_setting.h"
#include <EEPROM.h>
#include <SPI.h>

TV tv;

void setup() {
	tv.channel.read();
	tv.volume.read();
	tv.brightness.read();
	tv.contrast.read();
	tv.vertical.read();
	ChannelSetting::readAll();
	tv.channel.apply();
	tv.volume.apply();
	tv.brightness.apply();
	tv.contrast.apply();
	tv.vertical.apply();
}

void loop() {
  int key = read_key();
  if (key > 0) Screen::screens[Screen::index]->handle(tv, key);
}

int read_key() {
  return 0;
}

