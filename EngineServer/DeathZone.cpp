#include "DeathZone.h"
#include "TransformComponent.h"
#include "RigidBodyComponent.h"
#include "RectangleColliderComponent.h"
#include "KillComponent.h"

DeathZone::DeathZone(PhysicsEngineSettings* physSettings, Rect position)
{
	_transform = new TransformComponent(this, position, false);

	_rigidBody = new RigidBodyComponent(this, physSettings, true, false, false, false, false, false, false);

	_components[ComponentTypes::RectangleColliderComponent] = new RectangleColliderComponent(
		this, 0, 0, position.getWidth(), position.getHeight());

	_components[ComponentTypes::KillComponent] = new KillComponent(this);
}

DeathZone::DeathZone(const DeathZone& other, PhysicsEngineSettings* physSettings) : GameObject(other)
{
	_transform = new TransformComponent(*other._transform, this);
	_rigidBody = new RigidBodyComponent(*other._rigidBody, this, physSettings);
	
	_components[ComponentTypes::RectangleColliderComponent] = new RectangleColliderComponent(
		*static_cast<RectangleColliderComponent*>(other._components.at(ComponentTypes::RectangleColliderComponent)), this
	);

	_components[ComponentTypes::KillComponent] = new KillComponent(
		*static_cast<KillComponent*>(other._components.at(ComponentTypes::KillComponent)), this
	);
}
