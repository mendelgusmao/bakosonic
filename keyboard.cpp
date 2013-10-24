#include "keyboard.h"
#include "Arduino.h"
#include "const.h"

Keyboard::Keyboard(const int pin) :
_pin(pin)
{}

int Keyboard::read() {
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
