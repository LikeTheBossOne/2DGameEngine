#pragma once
#include <vector>
#include <map>

namespace zmq {
	class socket_t;
}

class Entity;
class EntityManager;

class Game
{
public:
	Game();
	~Game();
	void run(zmq::socket_t& publisher);
	
	EntityManager* getEntityManager() { return _entityManager; }

	int getTotalPlayerCount() { return _totalPlayerCount; }
private:
	EntityManager* _entityManager;

	int _totalPlayerCount;
};

