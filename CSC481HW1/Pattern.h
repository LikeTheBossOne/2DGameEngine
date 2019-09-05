#pragma once
#include "PatternTypes.h"

class Pattern
{
public:
	Pattern(PatternTypes type, int ticksToComplete, float velocity);

	PatternTypes getType() { return _type; }
	int getTicksToComplete() { return _ticksToComplete; }
	float getVelocity() { return _velocity; }
private:
	PatternTypes _type;
	int _ticksToComplete;
	float _velocity;
};

