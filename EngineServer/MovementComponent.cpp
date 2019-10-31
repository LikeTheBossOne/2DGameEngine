#include "MovementComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "PlayerInputComponent.h"
#include "RigidBodyComponent.h"
#include "PhysicsEngineSettings.h"

MovementComponent::MovementComponent(GameObject* gameObject) : GenericComponent(gameObject)
{
	_velocityX = 0;
	_velocityY = 0;
}

void MovementComponent::update(int deltaTime)
{
	if (_gameObject->getRigidBody()->isStatic()) return;
	
	auto transform = _gameObject->getTransform();
	
	transform->setPositionX(transform->getPositionX() + _velocityX*float(deltaTime));
	transform->setPositionY(transform->getPositionY() - _velocityY*float(deltaTime));
}
