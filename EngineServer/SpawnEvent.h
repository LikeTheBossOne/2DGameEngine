#pragma once
#include "Event.h"

class Player;
class DeathEvent;
class GameObject;

class SpawnEvent : public Event
{
public:
	SpawnEvent(GameObject* spawningObject);
	std::string getType() override { return "Spawn"; }

	GameObject* spawningObject;
};

