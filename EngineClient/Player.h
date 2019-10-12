#pragma once
#include <SFML/Graphics/RectangleShape.hpp>
#include "Entity.h"
#include "Orientation.h"

class Platform;

class Player: public Entity
{
public:
	Player(Game* game, int GUID, sf::Texture* texture, sf::Vector2f location, sf::Vector2f size);
	Player(Game* game, int GUID, sf::Vector2f location, sf::Vector2f size);
	~Player();

	void tick(int deltaTime) override;
private:
	float _velocityX;
	float _velocityY;
	float _accelerationX;
	float _accelerationY;

	Platform* _groundPlat;

	Orientation _orientation;
};

