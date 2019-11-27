#pragma once
#include "Parameter.h"
class IntParameter : public Parameter
{
public:
	IntParameter(int value);
	ParameterType getType() override { return ParameterType::INTEGER; }

	int value;
};

