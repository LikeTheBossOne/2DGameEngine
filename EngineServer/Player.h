#pragma once
#include "Orientation.h"
#include "GameObject.h"
#include <string>
#include "Rect.h"
#include "EngineRectangle.h"

class SpawnZone;
class PhysicsEngineSettings;
class Game;
class Platform;

class Player: public GameObject
{
public:
	Player(PhysicsEngineSettings* physSettings, float width, float height, std::string textureName, SpawnZone* spawn);

	std::string getType() override { return "Player"; }
};

