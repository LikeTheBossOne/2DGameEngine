#include "Entity.h"

Entity::Entity(Game* game, sf::Vector2f size) : RectangleShape(size)
{
	_game = game;
}
