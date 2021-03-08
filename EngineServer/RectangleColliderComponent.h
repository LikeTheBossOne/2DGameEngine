#pragma once
#include "EngineRectangle.h"
#include "GenericComponent.h"

class MovementComponent;
class RigidBodyComponent;

class RectangleColliderComponent : public GenericComponent
{
public:
	RectangleColliderComponent(GameObject* gameObject, float relativeLeft, float relativeTop, float width, float height);
	RectangleColliderComponent(const RectangleColliderComponent& other, GameObject* gameObject);

	void update(int deltaTime) override;
	ComponentTypes getType() override { return ComponentTypes::RectangleColliderComponent; };

	void setBounds(EngineRectangle bounds) { _bounds = bounds; }
	void setBounds(float x, float y);
	void moveBounds(float x, float y);
	
	EngineRectangle getBounds() { return _bounds; }
	float getRelativeLeftBounds() { return _relativeLeftBounds; }
	float getRelativeTopBounds() { return _relativeTopBounds; }
private:
	EngineRectangle _bounds;

	float _relativeLeftBounds;
	float _relativeTopBounds;
};

