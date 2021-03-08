#pragma once
#include "Event.h"
#include "GameObject.h"
#include <map>

class StartReplayEvent : public Event
{
public:
	StartReplayEvent(std::map<int, GameObject*> entities);
	
	std::string getType() override { return "START_REP"; }

	std::map<int, GameObject*> entities;
};

