#pragma once
#include <vector>

class Entity;

class Game
{
public:
	Game();
	void run();
	std::vector<Entity*> getEntities() { return _entities; }
private:
	std::vector<Entity*> _entities;
};

