#include "Entity.h"

Entity::Entity(Game* game, int GUID, sf::Vector2f size) : RectangleShape(size)
{	
	_game = game;
	_GUID = GUID;
}

void Entity::tick(int deltaTime)
{
}
