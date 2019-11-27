#pragma once
#include <vector>
#include "GenericComponent.h"

class PlayerInputComponent : public GenericComponent
{
public:
	PlayerInputComponent(GameObject* gameObject, float leftVelocity, float rightVelocity);
	PlayerInputComponent(const PlayerInputComponent& other, GameObject* gameObject);

	void update(int deltaTime) override;
	ComponentTypes getType() override { return ComponentTypes::PlayerInputComponent; }
private:

	float _leftPressedVelocity;
	float _rightPressedVelocity;
};

