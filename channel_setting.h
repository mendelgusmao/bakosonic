#include "setting.h"

#ifndef CHANNEL_H
#define CHANNEL_H

class ChannelSetting : public Setting {
public:
	static int channels[CHAN_CEIL];

	ChannelSetting(const int address, const int defaultValue, const int lowerBound, const int upperBound) : 
		Setting(address, defaultValue, lowerBound, upperBound) {}

	void apply();
};

#endif // CHANNEL_H