#ifndef SETTING_H
#define SETTING_H

class Setting {
protected:
	int address;
	int value;
	int lowerBound;
	int upperBound;

public:
	Setting(int address, int defaultValue, int lowerBound, int upperBound);
	int operator++();
	int operator--();
	int get();
	int read();
	void write();
	void apply();
};

#endif // SETTING_H