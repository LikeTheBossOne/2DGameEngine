#pragma once
#include "GameObject.h"
class SideBoundary : public GameObject
{
public:
	SideBoundary(int GUID, float xPlane, float sceneShiftWidth);

	GameObjectTypes getType() override { return GameObjectTypes::SideBoundary; };
};

