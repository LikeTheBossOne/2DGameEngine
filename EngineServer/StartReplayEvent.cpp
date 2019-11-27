#include "StartReplayEvent.h"

StartReplayEvent::StartReplayEvent(std::map<int, GameObject*> entities) : Event(1, 0)
{
	this->entities = entities;
}
