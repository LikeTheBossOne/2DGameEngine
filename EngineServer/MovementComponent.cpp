#include "MovementComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "PlayerInputComponent.h"
#include "RigidBodyComponent.h"
#include "PhysicsEngineSettings.h"
#include <dukglue/dukglue.h>
#include "ScriptManager.h"

bool MovementComponent::scriptInitialized = false;

MovementComponent::MovementComponent(GameObject* gameObject) : GenericComponent(gameObject)
{
	if (!scriptInitialized)
	{
		// ScriptManager::getInstance()->registerScript("TransformComponent.update", "scripts/MovementComponent.js", "update");

		duk_context* ctx = ScriptManager::getInstance()->getContext();
		dukglue_register_property(ctx, &MovementComponent::getVelocityX, &MovementComponent::setVelocityX, "velocityX");
		dukglue_register_property(ctx, &MovementComponent::getVelocityY, &MovementComponent::setVelocityY, "velocityY");
		
		
		scriptInitialized = true;
	}
	_velocityX = 0;
	_velocityY = 0;
}

MovementComponent::MovementComponent(const MovementComponent& other, GameObject* gameObject) : GenericComponent(gameObject)
{
	_velocityX = other._velocityX;
	_velocityY = other._velocityY;
}

void MovementComponent::update(int deltaTime)
{
	if (_gameObject->getRigidBody()->isStatic()) return;
	
	auto transform = _gameObject->getTransform();
	
	transform->setPositionX(transform->getPositionX() + _velocityX*float(deltaTime));
	transform->setPositionY(transform->getPositionY() - _velocityY*float(deltaTime));
}
