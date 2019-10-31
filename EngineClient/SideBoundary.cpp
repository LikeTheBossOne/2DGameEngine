#include "SideBoundary.h"
#include "TransformComponent.h"
#include "SideBoundaryComponent.h"
#include "GenericComponent.h"

SideBoundary::SideBoundary(int GUID, float xPlane, float sceneShiftWidth) : GameObject(GUID)
{
	_transform = new TransformComponent(this, sf::FloatRect(xPlane, -1000, 1, 2000), false);

	_components[ComponentTypes::SideBoundaryComponent] = new SideBoundaryComponent(this, sceneShiftWidth);
}
