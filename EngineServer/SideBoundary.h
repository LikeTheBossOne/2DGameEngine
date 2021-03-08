#pragma once
#include "GameObject.h"
class PhysicsEngineSettings;

class SideBoundary : public GameObject
{
public:
	SideBoundary(PhysicsEngineSettings* physSettings, float x, float sceneShiftWidth);
	SideBoundary(const SideBoundary& other, PhysicsEngineSettings* physSettings);

	std::string getType() override { return "SideBoundary"; }
};

