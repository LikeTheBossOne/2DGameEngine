#pragma once
#include "ComponentTypes.h"
#include <unordered_map>

class GenericComponent;
class TransformComponent;
class RigidBodyComponent;

class GameObject
{
public:
	GameObject();
	virtual ~GameObject() = default;

	int getGUID() { return _GUID; }

	virtual std::string getType() = 0;

	GenericComponent* getComponent(ComponentTypes type) { return _components[type]; }
	TransformComponent* getTransform() { return _transform; }
	RigidBodyComponent* getRigidBody() { return _rigidBody; }
protected:
	int _GUID;
	static int nextId;
	
	std::unordered_map<ComponentTypes, GenericComponent*> _components;

	TransformComponent* _transform;
	RigidBodyComponent* _rigidBody;
};

