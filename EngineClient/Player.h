#pragma once
#include <SFML/Graphics/RectangleShape.hpp>
#include "Orientation.h"
#include "GameObject.h"

class Player : public GameObject
{
public:
	Player(int GUID, sf::FloatRect location);

	GameObjectTypes getType() override { return GameObjectTypes::Player; }
};

