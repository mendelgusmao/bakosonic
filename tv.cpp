#include <Arduino.h>
#include "tv.h"


void TV::toggle() {
  digitalWrite(PIN_RELAY, (on = !on) ? HIGH : LOW);
}

bool TV::isOn() {
  return on;
}

