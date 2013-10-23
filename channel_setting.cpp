#include "const.h"
#include "channel_setting.h"
#include <SPI.h>

void ChannelSetting::apply() {
	int position = ChannelSetting::channels[_value];

  digitalWrite(PIN_DIGIPOT, LOW);
  SPI.transfer(ADDRESS_CHANNEL);
  SPI.transfer(position);
  digitalWrite(PIN_DIGIPOT, HIGH);
}
