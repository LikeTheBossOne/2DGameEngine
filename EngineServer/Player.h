#pragma once
#include "Orientation.h"
#include "GameObject.h"
#include <string>
#include "Rect.h"
#include "EngineRectangle.h"

class PhysicsEngineSettings;
class Game;
class Platform;

class Player: public GameObject
{
public:
	Player(PhysicsEngineSettings* physSettings, Rect position, std::string textureName);

	std::string getType() override { return "Player"; }
};

