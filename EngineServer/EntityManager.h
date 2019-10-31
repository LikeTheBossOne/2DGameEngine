#pragma once
#include <map>
#include <mutex>
#include <vector>

class GameObject;
class Game;
class CollisionsManager;
class PhysicsEngineSettings;
class SpawnZone;

class EntityManager
{
public:
	EntityManager(Game* game);

	void update(int deltaTime);
	
	void addEntity(GameObject* entity);
	void deleteEntity(int GUID);
	void addSpawn(SpawnZone* spawn);

	std::map<int, GameObject*> getEntities();
	std::vector<SpawnZone*> getSpawns() { return _spawns; }

	PhysicsEngineSettings* getPhysicsEngineSettings() { return _physicsEngineSettings; }
private:
	Game* _game;

	CollisionsManager* _collisionsManager;

	PhysicsEngineSettings* _physicsEngineSettings;
	
	std::map<int, GameObject*> _entities;
	int _totalEntitiesToDate;

	std::vector<SpawnZone*> _spawns;

	std::mutex _entitiesLock;
};

