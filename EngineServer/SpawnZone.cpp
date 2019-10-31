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
