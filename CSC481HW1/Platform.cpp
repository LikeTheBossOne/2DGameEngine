#include "Platform.h"
#include <SFML/System/Time.hpp>

Platform::Platform(Game* game, sf::Texture* texture, sf::Vector2f location, sf::Vector2f size) : Entity(game, size)
{
	this->setPosition(location);
	this->setTexture(texture);
}

Platform::Platform(Game* game, sf::Vector2f location, sf::Vector2f size) : Entity(game, size)
{
	this->setPosition(location);
	this->setFillColor(sf::Color(150, 50, 250));
}

void Platform::tick(int deltaTime)
{
	
}
