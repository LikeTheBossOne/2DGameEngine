#pragma once
#include "ComponentTypes.h"
#include <unordered_map>
#include <SFML/Graphics/RectangleShape.hpp>
#include "GameObjectTypes.h"

class GenericComponent;
class TransformComponent;

class GameObject
{
public:
	GameObject(int GUID);
	virtual ~GameObject() = default;

	int getGUID() { return _GUID; }

	virtual GameObjectTypes getType() = 0;

	GenericComponent* getComponent(ComponentTypes type) { return _components[type]; }
	TransformComponent* getTransform() { return _transform; }
	sf::RectangleShape* getSFRectangleShape() { return _sfRectangleShape; }
protected:
	int _GUID;

	std::unordered_map<ComponentTypes, GenericComponent*> _components;

	TransformComponent* _transform;
	sf::RectangleShape* _sfRectangleShape;
};

