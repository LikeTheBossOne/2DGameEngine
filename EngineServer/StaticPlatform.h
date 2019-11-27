#pragma once
#include "GameObject.h"
#include <string>
#include "Rect.h"
#include "EngineRectangle.h"

class PhysicsEngineSettings;

class StaticPlatform : public GameObject
{
public:
	StaticPlatform(PhysicsEngineSettings* physSettings, Rect position, int r, int g, int b);
	StaticPlatform(const StaticPlatform& other, PhysicsEngineSettings* physSettings);

	std::string getType() override { return "StaticPlatform"; }
};

