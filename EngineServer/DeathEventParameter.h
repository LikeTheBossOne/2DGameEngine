#pragma once
#include "Parameter.h"
class DeathEvent;

class DeathEventParameter : public Parameter
{
public:
	DeathEventParameter(DeathEvent* value);
	
	ParameterType getType() override { return ParameterType::DEATH_EVENT; }

	DeathEvent* value;
};

