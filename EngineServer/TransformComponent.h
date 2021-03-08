#pragma once
#include "Rect.h"
#include "GenericComponent.h"

class MovementComponent;

class TransformComponent : public GenericComponent
{
public:
	static bool scriptInitialized;

	TransformComponent(GameObject* gameObject, Rect position, bool isVisible);
	TransformComponent(const TransformComponent& other, GameObject* gameObject);

	void update(int deltaTime) override;

	ComponentTypes getType() override { return ComponentTypes::TransformComponent; }

	void setPositionX(float x) { _position.setX(x); }
	void setPositionY(float y) { _position.setY(y); }
	void setWidth(float width) { _position.setWidth(width); }
	void setHeight(float height) { _position.setHeight(height); }
	void setIsVisible(bool isVisible) { _isVisible = isVisible; }

	float getPositionX() { return _position.getX(); }
	float getPositionY() { return _position.getY(); }
	float getWidth() { return _position.getWidth(); }
	float getHeight() { return _position.getHeight(); }
	bool isVisible() { return _isVisible; }
	float getPrevX() { return _prevX; }
	float getPrevY() { return _prevY; }
private:
	Rect _position;

	bool _isVisible;

	float _prevX;
	float _prevY;

	void setPrevX(float prevX) { _prevX = prevX; }
	void setPrevY(float prevY) { _prevY = prevY; }
};

