#pragma once
#include <vector>

namespace sf {
	class RenderWindow;
}

class Entity;
class Player;

class EntityManager
{
public:
	EntityManager();

	void setPlayer(Player* player);
	void addEntity(Entity* entity);

	std::vector<Entity*> getEntities() { return _entities; }
	
	void tick(int deltaTime);
	void draw(sf::RenderWindow& window);
private:

	std::vector<Entity*> _entities;
	Player* _player;
};

