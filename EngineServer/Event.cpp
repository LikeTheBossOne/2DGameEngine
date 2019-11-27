#include "Event.h"

Event::Event(int priority, int timeTillHandle)
{
	_priority = priority;

	_timestamp = 0;
	_timeTillHandle = timeTillHandle;
	_toHandleTimestamp = 0;
}
