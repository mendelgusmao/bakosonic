#include "const.h"
#include <EEPROM.h>
#include <SPI.h>

int oldChannel;
int oldBrightness;
int oldContrast;
int oldVertical;

class Setting {
protected:
  int _address;
  int _offset;
  int _value;
  int _lowerBound;
  int _upperBound;

public:
	Setting(const int address, const int offset, const int lowerBound, const int upperBound) :
	_address(address),
	_offset(offset),
	_value(lowerBound),
	_lowerBound(lowerBound),
	_upperBound(upperBound)
	{
	}

	virtual int operator++() {
	  if (_value == _upperBound) return 0;
	  apply();
	  return ++_value;
	}

	virtual int operator--() {
	  if (_value == _lowerBound) return 0;
	  apply();
	  return --_value;
	}

	virtual int get() {
	  return _value;
	}

	virtual void set(const int value) {
	  _value = value;
	  apply();
	}

	virtual int read() {
	  return EEPROM.read(_address + _offset);
	}

	virtual void write() {
	  EEPROM.write(_address + _offset, _value);
	}

	virtual void apply() {
	  digitalWrite(PIN_DIGIPOT_CS, LOW);
	  SPI.transfer(_address);
	  SPI.transfer(_value);
	  digitalWrite(PIN_DIGIPOT_CS, HIGH);
	}

	virtual void setOffset(const int offset) {
	  _offset = offset;
	}
};

class ChannelSetting : 
public Setting {
public:
  static int channels[CHAN_CEIL];

  Setting tuning;

  ChannelSetting(const int address, const int offset, const int lowerBound, const int upperBound) : 
  Setting(address, offset, lowerBound, upperBound),
  tuning(EEPROM_OFFSET, 0, 0, 255) {
  }

	static void readAll() {
	  for (int index = CHAN_FLOOR + EEPROM_OFFSET; index <= CHAN_CEIL + EEPROM_OFFSET; index++) {
	    ChannelSetting::channels[index] = EEPROM.read(index);
	  }
	}

	int operator++() {
	  _value = _value == _upperBound ? _lowerBound : _value + 1;
	  apply();
	  return _value;
	}

	int operator--() {
	  _value = _value == _lowerBound ? _upperBound : _value - 1;
	  apply();
	  return _value;
	}

	void set(const int value) {
	  _value = value;
	  apply();
	}

	void apply() {
	  tuning.set(channels[_value]);
	  tuning.apply();
	}

	void write() {
	  EEPROM.write(_address, _value);

	  tuning.setOffset(_value);
	  channels[_value] = tuning.get();
	  tuning.write();
	}

	const int band() {
	  if (_value >= 2 && _value <= 6) {
	    return CHAN_BAND_VHF_LOW;
	  } 
	  else if (_value >= 7 && _value <= 13) {
	    return CHAN_BAND_VHF_HIGH;
	  }

	  return CHAN_BAND_UHF;
	}
};

int ChannelSetting::channels[CHAN_CEIL];

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

  void toggle() {
    digitalWrite(_pinRelay, (_on = !_on) ? HIGH : LOW);
  }

  bool isOn() {
    return _on;
  }
};

class Screen {
public:
  static int index;
  static Screen* screens[SCREENS];
  void handle(TV &tv, const int key);
};

class StandbyScreen : 
public Screen {
public:
	void handle(TV &tv, const int key) {
	  if (key != KEY_ONOFF) return;
	  tv.toggle();
	  Screen::index = SCREEN_MAIN;
	}
};

class MainScreen : 
public Screen {
public:
	void handle(TV &tv, const int key) {
	  switch (key) {
	  case KEY_ONOFF:
	    tv.toggle();
	    break;

	  case KEY_CHAN_UP:
	    ++tv.channel;
	    tv.channel.write();
	    break;

	  case KEY_CHAN_DOWN:
	    --tv.channel;
	    tv.channel.write();
	    break;

	  case KEY_VOL_UP:
	    ++tv.volume;
	    tv.volume.write();
	    break;

	  case KEY_VOL_DOWN:
	    --tv.volume;
	    tv.volume.write();
	    break;

	  case KEY_SETUP:
	    oldChannel = tv.channel.get();
	    oldBrightness = tv.brightness.get();
	    oldContrast = tv.contrast.get();
	    oldVertical = tv.vertical.get();

	    Screen::index = SCREEN_TUNING;
	    break;	
	  }
	}
};

class TuningScreen : 
public Screen {
public:
	void handle(TV &tv, const int key) {
	  switch (key) {
	  case KEY_ONOFF:
	    tv.channel.write();

	    Screen::index = SCREEN_MAIN;
	    break;

	  case KEY_CHAN_UP:
	    ++tv.channel;
	    break;

	  case KEY_CHAN_DOWN:
	    --tv.channel;
	    break;

	  case KEY_VOL_UP:
	    ++tv.channel.tuning;
	    break;

	  case KEY_VOL_DOWN:
	    --tv.channel.tuning;
	    break;

	  case KEY_SETUP:
	    Screen::index = SCREEN_SETUP;
	    break;  
	  }
	}
};

class SetupScreen : 
public Screen {
public:
	void handle(TV &tv, const int key) {
	  switch (key) {
	  case KEY_ONOFF:
	    tv.channel.set(oldChannel);
	    tv.brightness.write();
	    tv.contrast.write();
	    tv.vertical.write();

	    Screen::index = SCREEN_MAIN;
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
	    tv.channel.set(oldChannel);
	    tv.brightness.set(oldBrightness);
	    tv.contrast.set(oldContrast);
	    tv.vertical.set(oldVertical);

	    Screen::index = SCREEN_MAIN;
	    break;  
	  }  
	}
};

class Keyboard {
private:
	int _pin;

public:
	Keyboard(const int pin) :
	_pin(pin)
	{}

	int read() {
		long counter = 0;
		int key = 0;

		pinMode(_pin, OUTPUT);
		digitalWrite(_pin, HIGH);
		delay(4);
		pinMode(_pin, INPUT);
		digitalWrite(_pin, LOW);

		while (digitalRead(_pin)) {
			counter++;
		}

		return key;
	}
};

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
