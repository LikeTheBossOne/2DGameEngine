#pragma once
#include "Event.h"

class GameObject;

class DeathEvent : public Event
{
public:
	DeathEvent(GameObject* dyingObject);
	
	std::string getType() override { return "Death"; }

	void setDyingObject(GameObject* dyingObject) { _dyingObject = dyingObject; }

	GameObject* getDyingObject() { return _dyingObject; }
private:
	GameObject* _dyingObject;
};

