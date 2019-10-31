#include "RigidBodyComponent.h"
#include "MovementComponent.h"
#include "PhysicsEngineSettings.h"
#include "GameObject.h"
#include "TransformComponent.h"

RigidBodyComponent::RigidBodyComponent(GameObject* gameObject, PhysicsEngineSettings* physicsEngineSettings) : GenericComponent(gameObject)
{
	_physicsEngineSettings = physicsEngineSettings;
	
	_isStatic = false;
	_ignoreCollisions = false;

	_useGravity = false;
	_isStickySurface = false;
	_canStickToSurface = false;
	_isPushable = false;
	_canPush = false;

	_stuckToEntity = nullptr;
}

RigidBodyComponent::RigidBodyComponent(GameObject* gameObject, PhysicsEngineSettings* physicsEngineSettings,
                                       bool isStatic, bool ignoreCollisions, bool useGravity, bool isSticky,
                                       bool canStickToSurface, bool isPushable, bool canPush) : GenericComponent(gameObject)
{
	_physicsEngineSettings = physicsEngineSettings;
	
	_isStatic = isStatic;
	_ignoreCollisions = ignoreCollisions;

	_useGravity = useGravity;
	_isStickySurface = isSticky;
	_canStickToSurface = canStickToSurface;
	_isPushable = isPushable;
	_canPush = canPush;

	_stuckToEntity = nullptr;
}

void RigidBodyComponent::update(int deltaTime)
{
	// Move transform by velocity of component it is stuck to
	if (_stuckToEntity != nullptr)
	{
		const auto gMovement = _gameObject->getComponent(ComponentTypes::MovementComponent);
		if (gMovement != nullptr)
		{
			auto movement = dynamic_cast<MovementComponent*>(gMovement);

			const auto gMoveOther = _stuckToEntity->getComponent(ComponentTypes::MovementComponent);
			if (gMoveOther != nullptr)
			{
				auto moveOther = dynamic_cast<MovementComponent*>(gMoveOther);

				movement->setVelocityX(movement->getVelocityX() + moveOther->getVelocityX());
				movement->setVelocityY(movement->getVelocityX() + moveOther->getVelocityY());
			}
		}
	}
	else if (_useGravity)
	{
		const auto gMovement = _gameObject->getComponent(ComponentTypes::MovementComponent);
		if (gMovement != nullptr)
		{
			auto movement = dynamic_cast<MovementComponent*>(gMovement);
			movement->setVelocityY(movement->getVelocityY() + _physicsEngineSettings->getGravityY() * float(deltaTime));
		}
	}
}
