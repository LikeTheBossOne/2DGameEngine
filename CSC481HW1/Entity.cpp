#include "Entity.h"

Entity::Entity(Game* game, int GUID, sf::Vector2f size) : RectangleShape(size)
{
	this->setFillColor(sf::Color(150, 50, 250));
	
	_game = game;
	this->_GUID = GUID;
}

void Entity::tick(int deltaTime)
{
}
