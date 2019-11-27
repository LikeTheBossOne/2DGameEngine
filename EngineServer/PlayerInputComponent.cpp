#include "PlayerInputComponent.h"
#include "Inputs.h"
#include "GameObject.h"
#include "MovementComponent.h"
#include "JumpComponent.h"
#include "InputManager.h"
#include <iostream>

PlayerInputComponent::PlayerInputComponent(GameObject* gameObject, float leftVelocity, float rightVelocity) : GenericComponent(gameObject)
{
	_leftPressedVelocity = leftVelocity;
	_rightPressedVelocity = rightVelocity;
}

PlayerInputComponent::PlayerInputComponent(const PlayerInputComponent& other, GameObject* gameObject) : GenericComponent(gameObject)
{
	_leftPressedVelocity = other._leftPressedVelocity;
	_rightPressedVelocity = other._rightPressedVelocity;
}

void PlayerInputComponent::update(int deltaTime)
{
	const auto inputs = InputManager::getInstance()->getInputs(_gameObject->getGUID());
	// if (inputs.empty()) return;
	
	const auto gMovement = _gameObject->getComponent(ComponentTypes::MovementComponent);
	auto movement = gMovement != nullptr ? dynamic_cast<MovementComponent*>(gMovement) : nullptr;
	if (inputs[int(Inputs::LEFT)] && movement != nullptr)
	{
		if (movement->getVelocityX() > _leftPressedVelocity)
		{
			movement->setVelocityX(movement->getVelocityX() + _leftPressedVelocity);
		}
	} else if (inputs[int(Inputs::RIGHT)] && movement != nullptr)
	{
		if (movement->getVelocityX() < _rightPressedVelocity)
		{
			movement->setVelocityX(movement->getVelocityX() + _rightPressedVelocity);
		}
	} else
	{
		movement->setVelocityX(0);
	}
	// std::cout << inputs[0] << inputs[1] << inputs[2] << std::endl;

	const auto gJump = _gameObject->getComponent(ComponentTypes::JumpComponent);
	auto jump = gJump != nullptr ? dynamic_cast<JumpComponent*>(gJump) : nullptr;
	
	if (inputs[int(Inputs::UP)] && jump != nullptr && !jump->isJumping())
	{
		jump->setShouldJump(true);
	}
}
