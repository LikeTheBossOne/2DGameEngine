#pragma once
#include <map>
#include <mutex>

class Entity;
class Player;
class Game;

class EntityManager
{
public:
	EntityManager(Game* game);

	void addPlayer(Player* player);
	void addEntity(Entity* entity);

	std::map<int, Entity*> getEntities() { return _entities; };
	std::map<int, Player*> getPlayers() { return _players; };
	
	void tick(int deltaTime);
	
private:
	Game* _game;
	
	std::map<int, Entity*> _entities;
	std::map<int, Player*> _players;

	std::mutex _playerLock;
};

