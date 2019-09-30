#pragma once
#include <SFML/Graphics/RectangleShape.hpp>

namespace sf {
	class Time;
}
class Game;

class Entity : public sf::RectangleShape
{
public:
	Entity(Game* game, int GUID, sf::Vector2f size);
	virtual void tick(int deltaTime);

	int getGUID() { return _GUID; }
protected:
	Game* _game;
private:
	int _GUID;
};

