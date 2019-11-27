#pragma once
#include "Parameter.h"
class EventManager;

class EventManagerParameter :public Parameter
{
public:
	EventManagerParameter(EventManager* value);
	ParameterType getType() override { return ParameterType::EVENT_MANAGER; }

	EventManager* value;
};

