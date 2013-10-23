#include <Arduino.h>
#include "tv.h"


void TV::toggle() {
  digitalWrite(PIN_RELAY, (_on = !_on) ? HIGH : LOW);
}

bool TV::isOn() {
  return _on;
}


