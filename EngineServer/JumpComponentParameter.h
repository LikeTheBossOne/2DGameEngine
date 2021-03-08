#pragma once
#include "Parameter.h"
class JumpComponent;

class JumpComponentParameter : public Parameter
{
public:
	JumpComponentParameter(JumpComponent* value);
	
	ParameterType getType() override { return ParameterType::JUMP_COMPONENT; }

	JumpComponent* value;
};

