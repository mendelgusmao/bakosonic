#include <EEPROM.h>
#include "const.h"
#include "tv.h"
#include "screen.h"
#include "setting.h"

TV tv;
MainScreen main;
TuningScreen tuning;
SetupScreen setups;
StandbyScreen standby;

Screen* screens[4] = {
  screens[SCREEN_STANDBY] = &standby,
  screens[SCREEN_MAIN] = &main,
  screens[SCREEN_TUNING] = &tuning,
  screens[SCREEN_SETUP] = &setups
};

void setup() {}

void loop() {
  int key = read_key();
  screens[Screen::index]->handle(tv, key);
}

int read_key() {
  return 0;
}

