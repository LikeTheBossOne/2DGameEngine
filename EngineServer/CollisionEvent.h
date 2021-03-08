#pragma once
#include "Event.h"

class GameObject;

class CollisionEvent : public Event
{
public:
	CollisionEvent(GameObject* first, GameObject* second);
	std::string getType() override { return "Col"; }
	
	GameObject* first;
	GameObject* second;
};

