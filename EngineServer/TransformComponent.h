#pragma once
#include "Rect.h"
#include "GenericComponent.h"

class MovementComponent;

class TransformComponent : public GenericComponent
{
public:
	TransformComponent(GameObject* gameObject, Rect position);

	void update(int deltaTime) override;

	ComponentTypes getType() override { return ComponentTypes::TransformComponent; }

	void setPositionX(float x) { _position.setX(x); }
	void setPositionY(float y) { _position.setY(y); }
	void setWidth(float width) { _position.setWidth(width); }
	void setHeight(float height) { _position.setHeight(height); }
	
	float getPositionX() { return _position.getX(); }
	float getPositionY() { return _position.getY(); }
	float getWidth() { return _position.getWidth(); }
	float getHeight() { return _position.getHeight(); }
	float getPrevX() { return _prevX; }
	float getPrevY() { return _prevY; }
private:
	Rect _position;

	float _prevX;
	float _prevY;
};

