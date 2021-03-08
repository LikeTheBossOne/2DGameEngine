#pragma once
#include "GameObject.h"
#include "Rect.h"

class PhysicsEngineSettings;

class SpawnZone : public GameObject
{
public:
	SpawnZone(PhysicsEngineSettings* physSettings, float x, float y);
	SpawnZone(const SpawnZone& other, PhysicsEngineSettings* physSettings);

	std::string getType() override { return "SpawnZone"; }
};

