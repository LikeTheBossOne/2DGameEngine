#pragma once
#include "GameObject.h"
class PhysicsEngineSettings;

class SideBoundary : public GameObject
{
public:
	SideBoundary(PhysicsEngineSettings* physSettings, float x, float sceneShiftWidth);

	std::string getType() override { return "SideBoundary"; }
};

