#pragma once
#include <map>
#include <mutex>
#include <vector>
#include "EventHandler.h"

class StartReplayEvent;
class GameObject;
class Game;
class CollisionsDetector;
class MovementSystem;
class LifeSystem;
class SpawnSystem;
class PhysicsEngineSettings;
class SpawnZone;

class EntityManager : public EventHandler
{
public:
	EntityManager(Game* game);

	void update(int deltaTime);
	
	void onEvent(Event* e) override;
	void handleStartReplay(StartReplayEvent* e);
	
	void addEntity(GameObject* entity);
	void deleteEntity(int GUID);
	void addSpawn(SpawnZone* spawn);

	void overwriteEntities(std::map<int, GameObject*> newEntitiesState) { _entities = newEntitiesState; }

	std::map<int, GameObject*> getEntities();
	std::vector<SpawnZone*> getSpawns() { return _spawns; }

	PhysicsEngineSettings* getPhysicsEngineSettings() { return _physicsEngineSettings; }
private:
	Game* _game;

	CollisionsDetector* _collisionsManager;
	MovementSystem* _movementSystem;
	LifeSystem* _lifeSystem;
	SpawnSystem* _spawnSystem;

	PhysicsEngineSettings* _physicsEngineSettings;
	
	std::map<int, GameObject*> _entities;
	int _totalEntitiesToDate;

	std::vector<SpawnZone*> _spawns;

	std::mutex _entitiesLock;
};

