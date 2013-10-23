#ifndef SETTING_H
#define SETTING_H

class Setting {
protected:
  int _address;
  int _offset;
  int _value;
  int _lowerBound;
  int _upperBound;

public:
  Setting(const int address, const int offset, const int lowerBound, const int upperBound);
  int operator++();
  int operator--();
  int get();
  int read();
  void write();
  void apply();
  void setOffset(const int offset);
};

#endif // SETTING_H


