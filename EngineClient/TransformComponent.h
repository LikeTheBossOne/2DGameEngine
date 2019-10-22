#pragma once
#include <SFML/Graphics/Rect.hpp>
#include "ComponentTypes.h"
#include "GenericComponent.h"

class GameObject;

class TransformComponent : public GenericComponent
{
public:
	TransformComponent(GameObject* gameObject, sf::FloatRect position);

	void update(int deltaTime) override;

	ComponentTypes getType() override { return ComponentTypes::TransformComponent; }

	void setPositionX(float x) { _position.left = x; }
	void setPositionY(float y) { _position.top = y; }
	void setWidth(float width) { _position.width = width; }
	void setHeight(float height) { _position.height = height; }

	float getPositionX() { return _position.left; }
	float getPositionY() { return _position.top; }
	float getWidth() { return _position.width; }
	float getHeight() { return _position.height; }
private:
	sf::FloatRect _position;
};

