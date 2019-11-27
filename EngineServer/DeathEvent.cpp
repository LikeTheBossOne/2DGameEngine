#include "DeathEvent.h"

DeathEvent::DeathEvent(GameObject* dyingObject) : Event(0, 0)
{
	_dyingObject = dyingObject;
}
