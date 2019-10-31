#pragma once
#include "GameObject.h"
class StaticPlatform : public GameObject
{
public:
	StaticPlatform(int GUID, sf::FloatRect location);

	GameObjectTypes getType() override { return GameObjectTypes::StaticPlatform; }
};

