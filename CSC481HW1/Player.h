#pragma once
#include <SFML/Graphics/RectangleShape.hpp>
#include "Entity.h"
#include "Orientation.h"

class Platform;

class Player: public sf::RectangleShape, public Entity
{
public:
	Player(Game* game, sf::Texture* texture, sf::Vector2f location, sf::Vector2f size);
	Player(Game* game, sf::Vector2f location, sf::Vector2f size);

	void tick(sf::Time deltaTime) override;
private:
	float _velocityX;
	float _velocityY;
	float _accelerationX;
	float _accelerationY;

	Platform* _groundPlat;

	Orientation _orientation;
};

