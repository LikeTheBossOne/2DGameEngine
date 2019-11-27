#include "SideBoundary.h"
#include "Rect.h"
#include "TransformComponent.h"
#include "RigidBodyComponent.h"
#include "SideBoundaryComponent.h"

SideBoundary::SideBoundary(PhysicsEngineSettings* physSettings, float x, float sceneShiftWidth)
{
	_transform = new TransformComponent(this, Rect(x, -1000, 1, 2000), false);

	_rigidBody = new RigidBodyComponent(this, physSettings, true, true, false, false, false, false, false);

	_components[ComponentTypes::SideBoundaryComponent] = new SideBoundaryComponent(this, sceneShiftWidth);
}

SideBoundary::SideBoundary(const SideBoundary& other, PhysicsEngineSettings* physSettings) : GameObject(other)
{
	_transform = new TransformComponent(*other._transform, this);
	_rigidBody = new RigidBodyComponent(*other._rigidBody, this, physSettings);
	
	_components[ComponentTypes::SideBoundaryComponent] = new SideBoundaryComponent(
		*static_cast<SideBoundaryComponent*>(other._components.at(ComponentTypes::SideBoundaryComponent)), this
	);
}
