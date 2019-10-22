#pragma once
#include <vector>
#include "GenericComponent.h"

class PlayerInputComponent : public GenericComponent
{
public:
	PlayerInputComponent(GameObject* gameObject, float leftVelocity, float rightVelocity);

	void update(int deltaTime) override;
	ComponentTypes getType() override { return ComponentTypes::PlayerInputComponent; }
private:

	float _leftPressedVelocity;
	float _rightPressedVelocity;
};

