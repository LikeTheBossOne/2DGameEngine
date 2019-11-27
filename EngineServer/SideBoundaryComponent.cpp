#include "SideBoundaryComponent.h"

SideBoundaryComponent::SideBoundaryComponent(GameObject* gameObject, float sceneShiftWidth) : GenericComponent(gameObject)
{
	_sceneShiftWidth = sceneShiftWidth;
}

SideBoundaryComponent::SideBoundaryComponent(const SideBoundaryComponent& other, GameObject* gameObject) : GenericComponent(gameObject)
{
	_sceneShiftWidth = other._sceneShiftWidth;
}

void SideBoundaryComponent::update(int deltaTime)
{
}
