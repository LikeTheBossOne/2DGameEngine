#include "CollisionEvent.h"

CollisionEvent::CollisionEvent(GameObject* first, GameObject* second) : Event(1, 0)
{
	this->first = first;
	this->second = second;
}
