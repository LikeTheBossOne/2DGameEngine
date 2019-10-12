#pragma once
#include <map>
#include <mutex>

class Game;

namespace sf {
	class RenderWindow;
}

class Entity;

class EntityManager
{
public:
	EntityManager(Game* game);

	void setEntity(int GUID, Entity* entity);
	void setPlayer(int GUID, Entity* entity);
	void setMyPlayer(Entity* player);

	void deletePlayer(int GUID, std::mutex& playersLock);
	
	std::map<int, Entity*> getEntities() { return _entities; }
	std::map<int, Entity*> getPlayers() { return _players; }
	Entity* getMyPlayer() { return _myPlayer; }
	
	void tick(int deltaTime);
	void draw(sf::RenderWindow& window, std::mutex& myPlayerLock, std::mutex& playersLock, std::mutex& entitiesLock);
private:
	Game* _game;
	
	std::map<int, Entity*> _entities;
	std::map<int, Entity*> _players;
	Entity* _myPlayer;
};

