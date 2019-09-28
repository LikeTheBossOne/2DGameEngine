#pragma once
#include <SFML/System/Vector2.hpp>
#include "Entity.h"
#include <SFML/Graphics/RectangleShape.hpp>

namespace sf {
	class Texture;
}

class Platform : public Entity
{
public:
	Platform(Game* game, sf::Texture* texture, sf::Vector2f location, sf::Vector2f size);
	Platform(Game* game, sf::Vector2f location, sf::Vector2f size);
	virtual void tick(int deltaTime);

	virtual float getCurrentVelocityX() { return 0; }
	virtual float getCurrentVelocityY() { return 0; }
};

