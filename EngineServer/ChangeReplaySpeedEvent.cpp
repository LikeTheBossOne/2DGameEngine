#include "ChangeReplaySpeedEvent.h"

ChangeReplaySpeedEvent::ChangeReplaySpeedEvent(float speed) : Event(1, 0)
{
	this->speed = speed;
}
