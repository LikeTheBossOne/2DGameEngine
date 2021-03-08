#pragma 
#include "Event.h"
class StopReplayEvent : public Event
{
public:
	StopReplayEvent();
	
	std::string getType() override { return "STOP_REP"; }
};

