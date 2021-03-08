#pragma once
#include <bitset>
#include <map>

class ReplayTick
{
public:
	ReplayTick(std::map<int, std::bitset<3>> inputs, int timeStamp);
	
	std::map<int, std::bitset<3>> getInputs() { return _inputs; }
	int getTimestamp() { return _timeStamp; }
private:
	std::map<int, std::bitset<3>> _inputs;

	int _timeStamp;
};

