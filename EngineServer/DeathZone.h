#pragma once
#include "GameObject.h"
#include "Rect.h"

class PhysicsEngineSettings;

class DeathZone : public GameObject
{
public:
	DeathZone(PhysicsEngineSettings* physSettings, Rect position);

	std::string getType() override { return "DeathZone"; }
};

