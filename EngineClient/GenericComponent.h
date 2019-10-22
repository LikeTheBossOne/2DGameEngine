#pragma once
#include "ComponentTypes.h"

class GameObject;

class GenericComponent
{
public:
	virtual ~GenericComponent() = default;
	GenericComponent(GameObject* gameObject);
	virtual void update(int deltaTime) = 0;
	virtual ComponentTypes getType() = 0;
protected:
	GameObject* _gameObject;
};
