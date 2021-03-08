#pragma once
#include "Event.h"

class Replay;

class StartRecordingEvent : public Event
{
public:
	StartRecordingEvent(Replay* replay);

	std::string getType() override { return "START_REC"; }

	Replay* replay;
};

