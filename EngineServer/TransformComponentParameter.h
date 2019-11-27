#pragma once
#include "Parameter.h"

class TransformComponent;

class TransformComponentParameter : public Parameter
{
public:
	TransformComponentParameter(TransformComponent* value);
	ParameterType getType() override { return ParameterType::TRANSFORM_COMPONENT; }

	TransformComponent* value;
};

