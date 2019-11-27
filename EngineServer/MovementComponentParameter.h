#pragma once
#include "Parameter.h"

class MovementComponent;

class MovementComponentParameter : public Parameter
{
public:
	MovementComponentParameter(MovementComponent* value);
	ParameterType getType() override { return ParameterType::MOVEMENT_COMPONENT; }

	MovementComponent* value;
};

