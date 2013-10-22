#include <EEPROM.h>
#include <SPI.h>
#include "const.h"

bool on = false;
int screen = SCREEN_MAIN;
int channel = 2; 
int volume = 0;
int brightness = 0;
int contrast = 0;
int vertical = 0;
int channels[CHAN_CEIL];

void setup() {
  channel = EEPROM.read(ADDRESS_TUNING);
  volume = EEPROM.read(ADDRESS_VOLUME);
  brightness = EEPROM.read(ADDRESS_BRIGHTNESS);
  contrast = EEPROM.read(ADDRESS_CONTRAST);
  vertical = EEPROM.read(ADDRESS_VERTICAL);
}

void loop() {
  int key = read_key();

  if (on) {
    switch (screen) {
    case SCREEN_MAIN:
      handle_main(key);
      break;

    case SCREEN_SETUP1:
      handle_setup1(key);
      break;

    case SCREEN_SETUP2:
      handle_setup2(key);
      break;
    }
  } 
  else {
    if (key = KEY_ONOFF) {
      toggle_tv();
    }
  }

  update_screen();
}

void handle_main(int key) {
  switch (key) {
  case KEY_ONOFF:
    toggle_tv();
    break;

  case KEY_CHAN_UP:
    ++channel;
    if (channel > CHAN_CEIL) channel = CHAN_FLOOR;
    set_channel(channel);
    break;

  case KEY_CHAN_DOWN:
    --channel;
    if (channel < CHAN_FLOOR) channel = CHAN_CEIL;
    set_channel(channel);
    break;

  case KEY_VOL_UP:
    if (volume == 255) return;
    volume++;
    set(ADDRESS_VOLUME, volume);
    break;

  case KEY_VOL_DOWN:
    if (volume == 0) return;
    volume--;
    set(ADDRESS_VOLUME, volume);
    break;

  case KEY_SETUP:
    change_screen(SCREEN_SETUP1);
    break;	
  }
}

void handle_setup1(int key) {
  switch (key) {
  case KEY_ONOFF:
    toggle_tv();
    break;

  case KEY_CHAN_UP:
    break;

  case KEY_CHAN_DOWN:
    break;

  case KEY_VOL_UP:
    break;

  case KEY_VOL_DOWN:
    break;

  case KEY_SETUP:
    change_screen(SCREEN_SETUP2);
    break;  
  }
}

void handle_setup2(int key) {
  switch (key) {
  case KEY_ONOFF:
    toggle_tv();
    break;

  case KEY_CHAN_UP:
    break;

  case KEY_CHAN_DOWN:
    break;

  case KEY_VOL_UP:
    break;

  case KEY_VOL_DOWN:
    break;

  case KEY_SETUP:
    change_screen(SCREEN_SETUP2);
    break;  
  }
}

void change_screen(int new_screen) {
  screen = new_screen;
  // TODO
}

void update_screen() {}

void toggle_tv() {
  digitalWrite(PIN_RELAY, (on = !on) ? HIGH : LOW);
  set_channel(channel);
  set(ADDRESS_VOLUME, volume);
  set(ADDRESS_BRIGHTNESS, brightness);
  set(ADDRESS_CONTRAST, contrast);
  set(ADDRESS_VERTICAL, vertical);
}

void set_channel(int new_channel) {
  channel = new_channel;
  int position = channels[channel];

  digitalWrite(PIN_DIGIPOT, LOW);
  SPI.transfer(ADDRESS_TUNING);
  SPI.transfer(position);
  digitalWrite(PIN_DIGIPOT, HIGH);

  EEPROM.write(ADDRESS_TUNING, channel);
}

int read_key() {
  return 0;
}

void set(int address, int value) {
  digitalWrite(PIN_DIGIPOT, LOW);
  SPI.transfer(address);
  SPI.transfer(value);
  digitalWrite(PIN_DIGIPOT, HIGH);

  EEPROM.write(address, value);
}