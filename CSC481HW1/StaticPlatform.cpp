#include "StaticPlatform.h"
#include "SFML/System/Time.hpp"

StaticPlatform::StaticPlatform(Game* game, sf::Texture* texture, sf::Vector2f location, sf::Vector2f size) : Platform(game, texture, location, size)
{
}

StaticPlatform::StaticPlatform(Game* game, sf::Vector2f location, sf::Vector2f size) : Platform(game, location, size)
{
}

void StaticPlatform::tick(sf::Time deltaTime)
{
}
