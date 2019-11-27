#include "JumpComponent.h"
#include "MovementComponent.h"
#include "GameObject.h"
#include <iostream>
#include <dukglue/dukglue.h>
#include "ScriptManager.h"
#include "JumpComponentParameter.h"
#include "MovementComponentParameter.h"
#include "TransformComponent.h"

bool JumpComponent::scriptInitialized = false;

JumpComponent::JumpComponent(GameObject* gameObject, float jumpAcceleration) : GenericComponent(gameObject)
{
	if (!scriptInitialized)
	{
		ScriptManager::getInstance()->registerScript("JumpComponent.update", "scripts/JumpComponent.js", "update");

		duk_context* ctx = ScriptManager::getInstance()->getContext();
		dukglue_register_property(ctx, &JumpComponent::getJumpAcceleration, &JumpComponent::setJumpAcceleration, "jumpAcceleration");
		dukglue_register_property(ctx, &JumpComponent::isJumping, &JumpComponent::setIsJumping, "isJumping");
		dukglue_register_property(ctx, &JumpComponent::shouldJump, &JumpComponent::setShouldJump, "shouldJump");
		
		scriptInitialized = true;
	}
	_jumpAcceleration = jumpAcceleration;
	_isJumping = false;
	_shouldJump = false;
}

JumpComponent::JumpComponent(const JumpComponent& other, GameObject* gameObject) : GenericComponent(gameObject)
{
	_jumpAcceleration = other._jumpAcceleration;
	_isJumping = other._isJumping;
	_shouldJump = other._shouldJump;
}

void JumpComponent::update(int deltaTime)
{
	auto gMovement = _gameObject->getComponent(ComponentTypes::MovementComponent);
	if (gMovement == nullptr) return;
	auto movement = dynamic_cast<MovementComponent*>(gMovement);
	
	
	JumpComponentParameter jumpParam(this);
	MovementComponentParameter moveParam(movement);
	
	std::vector<Parameter*> sParams;
	sParams.emplace_back(&jumpParam);
	sParams.emplace_back(&moveParam);

	ScriptReturnValue retVal(ParameterType::NONE);
	
	ScriptManager::getInstance()->run("JumpComponent.update", sParams, &retVal);
	
	// if (_shouldJump && !_isJumping)
	// {
	// 	
	//
	// 	movement->setVelocityY(movement->getVelocityY() + _jumpAcceleration);
	// 	std::cout << "JUMPING" << std::endl;
	// 	_isJumping = true;
	// 	_shouldJump = false;
	// }
}
