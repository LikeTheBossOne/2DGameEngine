#pragma once
#include "Event.h"

class StopRecordingEvent : public Event
{
public:
	StopRecordingEvent();

	std::string getType() override { return "STOP_REC"; }
};

