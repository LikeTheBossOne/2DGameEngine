#include "Pattern.h"

Pattern::Pattern(PatternTypes type, int ticksToComplete, float distance)
{
	_type = type;
	_gametimeToComplete = ticksToComplete;
	_distance = distance;
}
