#include "Pattern.h"

Pattern::Pattern(PatternTypes type, int ticksToComplete, float velocity)
{
	_type = type;
	_ticksToComplete = ticksToComplete;
	_velocity = velocity;
}
