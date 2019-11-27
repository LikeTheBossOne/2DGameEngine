#pragma once
#include <vector>
#include <map>

namespace zmq {
	class socket_t;
}

class GameTime;
class Entity;
class EntityManager;
class Replay;
class ReplaySystem;

class Game
{
public:
	Game();
	~Game();
	void run(zmq::socket_t& publisher);

	ReplaySystem* getReplaySystem() { return _replaySystem; }
	EntityManager* getEntityManager() { return _entityManager; }
	int getTotalPlayerCount() { return _totalPlayerCount; }
private:
	GameTime* _gameTime;
	EntityManager* _entityManager;
	ReplaySystem* _replaySystem;

	int _totalPlayerCount;

	static const int STEP_SIZE;
};

