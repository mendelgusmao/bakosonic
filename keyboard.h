#ifndef KEYBOARD_H
#define KEYBOARD_H
	
class Keyboard {
private:
	int _pin;

public:
	Keyboard(const int pin);
	int read();
};

#endif // KEYBOARD_H
