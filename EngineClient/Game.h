#pragma once
#include <string>
#include <SFML/Graphics/Texture.hpp>
#include <mutex>

namespace zmq {
	class socket_t;
}

class Entity;
class EntityManager;
class ResourceManager;

class Game
{
public:
	Game(int clientNumber, int playerNumber);
	~Game();
	void run(zmq::socket_t& socket, std::mutex& myPlayerLock, std::mutex& playersLock, std::mutex& entitiesLock);
	
	void setShouldStartYet(bool start) { _shouldStartYet = start; }
	
	EntityManager* getEntityManager() { return _entityManager; }
	ResourceManager* getResourceManager() { return _resourceManager; }
	
	int getClientNumber() { return _clientNumber; }
	int getPlayerNumber() { return _playerNumber; }
	bool getShouldStartYet() { return _shouldStartYet; }
	bool getShouldEnd() { return _shouldEnd; }
private:
	EntityManager* _entityManager;
	ResourceManager* _resourceManager;

	int _clientNumber;
	int _playerNumber;

	bool _shouldStartYet;
	bool _shouldEnd;
};

