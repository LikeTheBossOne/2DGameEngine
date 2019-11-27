#pragma once
#include "Event.h"

class ChangeReplaySpeedEvent : public Event
{
public:
	ChangeReplaySpeedEvent(float speed);
	
	std::string getType() override { return "REP_SPEED"; }

	float speed;
};

