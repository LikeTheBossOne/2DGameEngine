#include "SpawnEvent.h"
#include <iostream>
#include "Player.h"

SpawnEvent::SpawnEvent(GameObject* spawningObject) : Event(0, 5)
{
	this->spawningObject = spawningObject;
}