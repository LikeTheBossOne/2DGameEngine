#pragma once
#include "Parameter.h"
class NumberParameter : public Parameter
{
public:
	NumberParameter(double value);
	
	ParameterType getType() override { return ParameterType::NUMBER; }

	double value;
};

