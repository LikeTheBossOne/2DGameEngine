#pragma once
#include <vector>
#include <map>

namespace zmq {
	class socket_t;
}

class Entity;
class EntityManager;
class InputManager;

class Game
{
public:
	Game();
	~Game();
	void run(zmq::socket_t& publisher);
	
	EntityManager* getEntityManager() { return _entityManager; }
	InputManager* getInputManager() { return _inputManager; }
	std::map<int, Entity*> getEntities();

	int getTotalPlayerCount() { return _totalPlayerCount; }
private:
	EntityManager* _entityManager;
	InputManager* _inputManager;

	int _totalPlayerCount;
};

