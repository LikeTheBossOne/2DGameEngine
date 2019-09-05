#include "DynamicPlatform.h"
#include "SFML/System/Time.hpp"

DynamicPlatform::DynamicPlatform(Game* game, sf::Texture* texture, sf::Vector2f location, sf::Vector2f size) : Platform(game, texture, location, size)
{
	_prevX = location.x;
	_prevY = location.y;
}

DynamicPlatform::DynamicPlatform(Game* game, sf::Vector2f location, sf::Vector2f size) : Platform(game, location, size)
{
	_prevX = location.x;
	_prevY = location.y;
}

void DynamicPlatform::tick(sf::Time deltaTime)
{
	// TODO: tick tock
}
