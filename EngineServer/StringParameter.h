#pragma once
#include "Parameter.h"
class StringParameter : public Parameter
{
public:
	StringParameter(std::string value);
	ParameterType getType() override { return ParameterType::STRING; }

	std::string value;
};
