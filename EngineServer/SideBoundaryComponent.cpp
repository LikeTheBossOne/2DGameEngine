#include "SideBoundaryComponent.h"

SideBoundaryComponent::SideBoundaryComponent(GameObject* gameObject, float sceneShiftWidth) : GenericComponent(gameObject)
{
	_sceneShiftWidth = sceneShiftWidth;
}

void SideBoundaryComponent::update(int deltaTime)
{
}
