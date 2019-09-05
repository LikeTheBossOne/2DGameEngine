#pragma once

namespace sf {
	class Time;
}
class Game;

class Entity
{
public:
	Entity(Game* game);
	virtual void tick(sf::Time deltaTime) = 0;
	// virtual void draw(sf::RenderTarget& target) = 0;
protected:
	Game* _game;
};

