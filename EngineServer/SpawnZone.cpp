#include "SpawnZone.h"
#include "TransformComponent.h"
#include "RigidBodyComponent.h"
#include "PhysicsEngineSettings.h"
#include "SpawnComponent.h"

SpawnZone::SpawnZone(PhysicsEngineSettings* physSettings, float x, float y)
{
	_transform = new TransformComponent(this, Rect(x, y, 0, 0), false);

	_rigidBody = new RigidBodyComponent(this, physSettings, true, true, false, false, false, false, false);

	_components[ComponentTypes::SpawnComponent] = new SpawnComponent(this);

}

SpawnZone::SpawnZone(const SpawnZone& other, PhysicsEngineSettings* physSettings) : GameObject(other)
{
	_transform = new TransformComponent(*other._transform, this);
	_rigidBody = new RigidBodyComponent(*other._rigidBody, this, physSettings);
	
	_components[ComponentTypes::SpawnComponent] = new SpawnComponent(
		*static_cast<SpawnComponent*>(other._components.at(ComponentTypes::SpawnComponent)), this
	);
}
