#pragma once
#include <map>
#include <string>
#include <SFML/Graphics/Texture.hpp>
#include <mutex>

namespace zmq {
	class socket_t;
}

class Entity;
class EntityManager;

class Game
{
public:
	Game(int playerNumber);
	~Game();
	void run(zmq::socket_t& socket, std::mutex& myPlayerLock, std::mutex& playersLock, std::mutex& entitiesLock);

	void setTexture(std::string name, sf::Texture texture);
	void setShouldStartYet(bool start) { _shouldStartYet = start; }
	
	EntityManager* getEntityManager() { return _entityManager; }
	std::map<std::string, sf::Texture> getTexturesMap() { return _texturesMap; }
	int getPlayerNumber() { return _playerNumber; }
private:
	EntityManager* _entityManager;

	int _playerNumber;

	std::map<std::string, sf::Texture> _texturesMap;

	bool _shouldStartYet;
};

