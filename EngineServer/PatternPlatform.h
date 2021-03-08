#pragma once
#include "PatternTypes.h"
#include <vector>
#include "Rect.h"
#include "GameObject.h"

class PhysicsEngineSettings;
class Pattern;

class PatternPlatform : public GameObject
{
public:
	PatternPlatform(PhysicsEngineSettings* physSettings, Rect position, int r, int g, int b, std::vector<Pattern*> patterns);
	PatternPlatform(const PatternPlatform& other, PhysicsEngineSettings* physSettings);

	std::string getType() override { return "PatternPlatform"; }
};

