#include "const.h"
#include "tv.h"
#include "screen.h"
#include "setting.h"
#include "channel_setting.h"
#include "keyboard.h"
#include <EEPROM.h>
#include <SPI.h>

TV tv(PIN_RELAY);
Keyboard kb(PIN_KEYBOARD);

void setup() {
	ChannelSetting::readAll();
	tv.channel.read();
	tv.volume.read();
	tv.brightness.read();
	tv.contrast.read();
	tv.vertical.read();
	tv.channel.apply();
	tv.volume.apply();
	tv.brightness.apply();
	tv.contrast.apply();
	tv.vertical.apply();
}

void loop() {
  int key = kb.read();
  if (key > 0) Screen::screens[Screen::index]->handle(tv, key);
}
