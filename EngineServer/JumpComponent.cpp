#include "JumpComponent.h"
#include "MovementComponent.h"
#include "GameObject.h"
#include <iostream>

JumpComponent::JumpComponent(GameObject* gameObject, float jumpAcceleration) : GenericComponent(gameObject)
{	
	_jumpAcceleration = jumpAcceleration;
	_isJumping = false;
	_shouldJump = false;
}

void JumpComponent::update(int deltaTime)
{
	if (_shouldJump && !_isJumping)
	{
		auto gMovement = _gameObject->getComponent(ComponentTypes::MovementComponent);
		if (gMovement == nullptr) return;

		auto movement = dynamic_cast<MovementComponent*>(gMovement);

		movement->setVelocityY(movement->getVelocityY() + _jumpAcceleration);
		std::cout << "JUMPING" << std::endl;
		_isJumping = true;
		_shouldJump = false;
	}
}
