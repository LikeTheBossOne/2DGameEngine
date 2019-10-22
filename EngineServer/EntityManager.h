#pragma once
#include <map>
#include <mutex>
#include <vector>

class GameObject;
class Game;
class CollisionsManager;
class PhysicsEngineSettings;

class EntityManager
{
public:
	EntityManager(Game* game);

	void addEntity(GameObject* entity);
	void deleteEntity(int GUID);

	std::map<int, GameObject*> getEntities();
	
	void update(int deltaTime);

	PhysicsEngineSettings* getPhysicsEngineSettings() { return _physicsEngineSettings; }
private:
	Game* _game;

	CollisionsManager* _collisionsManager;

	PhysicsEngineSettings* _physicsEngineSettings;
	
	std::map<int, GameObject*> _entities;
	int _totalEntitiesToDate;

	std::mutex _entitiesLock;
};

