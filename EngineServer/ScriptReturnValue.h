#pragma once
#include "ParameterType.h"
#include "Parameter.h"

class ScriptReturnValue
{
public:
	ScriptReturnValue(ParameterType type);

	Parameter* value;
	size_t size;
	ParameterType type;
};

