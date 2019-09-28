#pragma once
#include <vector>

class Entity;
class EntityManager;

class Game
{
public:
	Game();
	~Game();
	void run();
	
	EntityManager* getEntityManager() { return _entityManager; }
	std::vector<Entity*> getEntities();
private:
	EntityManager* _entityManager;
};

