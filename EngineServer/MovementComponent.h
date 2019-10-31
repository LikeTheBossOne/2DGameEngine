#pragma once
#include "GenericComponent.h"

class RigidBodyComponent;
class PlayerInputComponent;
class PhysicsEngineSettings;

class MovementComponent : public GenericComponent
{
public:
	MovementComponent(GameObject* gameObject);

	void update(int deltaTime) override;
	ComponentTypes getType() override { return ComponentTypes::MovementComponent; };

	void setVelocityX(float velocityX) { _velocityX = velocityX; }
	void setVelocityY(float velocityY) { _velocityY = velocityY; }

	float getVelocityX() { return _velocityX; }
	float getVelocityY() { return _velocityY; }
private:
	float _velocityX;
	float _velocityY;
};

