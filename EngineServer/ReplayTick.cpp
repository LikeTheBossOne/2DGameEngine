#include "ReplayTick.h"

ReplayTick::ReplayTick(std::map<int, std::bitset<3>> inputs, int timeStamp)
{
	_inputs = inputs;
	_timeStamp = timeStamp;
}
