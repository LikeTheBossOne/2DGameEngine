#pragma once
#include "PatternTypes.h"

class Pattern
{
public:
	Pattern(PatternTypes type, int ticksToComplete, float distance);

	PatternTypes getType() { return _type; }
	int getGametimeToComplete() { return _gametimeToComplete; }
	float getDistance() { return _distance; }
private:
	PatternTypes _type;
	int _gametimeToComplete;
	float _distance;
};

