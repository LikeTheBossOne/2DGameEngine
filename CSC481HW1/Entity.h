#pragma once
#include <SFML/Graphics/RectangleShape.hpp>

namespace sf {
	class Time;
}
class Game;

class Entity : public sf::RectangleShape
{
public:
	Entity(Game* game, sf::Vector2f size);
	virtual void tick(int deltaTime) = 0;
	// virtual void draw(sf::RenderTarget& target) = 0;
protected:
	Game* _game;
};

