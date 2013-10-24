#ifndef CONST_H
#define CONST_H

const int SCREENS = 4;

const int SCREEN_STANDBY = 0;
const int SCREEN_MAIN = 1;
const int SCREEN_TUNING = 2;
const int SCREEN_SETUP = 3;

const int KEY_ONOFF = 0;
const int KEY_CHAN_UP = 1;
const int KEY_CHAN_DOWN = 2;
const int KEY_VOL_UP = 3;
const int KEY_VOL_DOWN = 4;
const int KEY_SETUP = 5;

const int PIN_BAND = 6;
const int PIN_RELAY = 9;
const int PIN_DIGIPOT_CS = 10;
const int PIN_DIGIPOT_SDI = 11;
const int PIN_DIGIPOT_CLK = 13;

const int CHAN_FLOOR = 2;
const int CHAN_CEIL = 83;
const int CHAN_BAND_VHF_LOW = 0;
const int CHAN_BAND_VHF_HIGH = 1;
const int CHAN_BAND_UHF = 2;

const int ADDRESS_CHANNEL = 0;
const int ADDRESS_VOLUME = 1;
const int ADDRESS_BRIGHTNESS = 2;
const int ADDRESS_CONTRAST = 3;
const int ADDRESS_VERTICAL = 4;
const int ADDRESS_BAND = 5;

const int EEPROM_OFFSET = ADDRESS_BAND + 1;

#endif CONST_H
