#pragma once
#include <map>
#include <mutex>

class Game;

namespace sf {
	class RenderWindow;
}

class GameObject;
class Player;
class SideBoundary;
class GameCamera;

class EntityManager
{
public:
	EntityManager(Game* game);

	void setEntity(int GUID, GameObject* entity);
	void addSideBoundary(int GUID, SideBoundary* sideBoundary);
	void setPlayer(int GUID, Player* entity);
	void setMyPlayer(Player* player);

	void deletePlayer(int GUID, std::mutex& playersLock);
	
	std::map<int, GameObject*> getEntities() { return _entities; }
	std::map<int, SideBoundary*> getSideBoundaries() { return _sideBoundaries; }
	std::map<int, Player*> getPlayers() { return _players; }
	Player* getMyPlayer() { return _myPlayer; }

	void update(std::mutex& myPlayerLock);
	void draw(sf::RenderWindow& window, std::mutex& myPlayerLock, std::mutex& playersLock, std::mutex& entitiesLock);
private:
	Game* _game;

	GameCamera* _gameCamera;
	
	std::map<int, GameObject*> _entities;
	std::map<int, SideBoundary*> _sideBoundaries;
	std::map<int, Player*> _players;
	Player* _myPlayer;
};

