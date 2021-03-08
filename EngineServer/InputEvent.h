#pragma once
#include "Event.h"
#include <vector>
#include <bitset>

class InputEvent : public Event
{
public:
	InputEvent(int playerGUID, std::bitset<3> inputs);
	std::string getType() override { return "Input"; }

	int playerGUID;
	std::bitset<3> inputs;
};

