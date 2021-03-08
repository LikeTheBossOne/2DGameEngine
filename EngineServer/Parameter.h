#pragma once
#include <string>
#include "JumpComponent.h"
#include "ParameterType.h"

class Parameter
{
public:
	Parameter() = default;
	virtual ~Parameter() = default;

	virtual ParameterType getType() = 0;
};
