#pragma once
#include <SFML/Graphics/Rect.hpp>
#include "GameObject.h"

class PatternPlatform : public GameObject
{
public:
	PatternPlatform(int GUID, sf::FloatRect location);

	GameObjectTypes getType() override { return GameObjectTypes::PatternPlatform; }
};
