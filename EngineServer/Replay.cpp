#include "Replay.h"
#include "GameObject.h"
#include "Player.h"
#include "SpawnZone.h"
#include "StaticPlatform.h"
#include "PatternPlatform.h"
#include "DeathZone.h"
#include "SideBoundary.h"
#include "SpawnableComponent.h"

Replay::Replay(std::map<int, GameObject*> initialEntitiesState, PhysicsEngineSettings* physSettings)
{
	_initialEntitiesState = std::map<int, GameObject*>();

	// Create Spawn Components
	for (auto pair : initialEntitiesState)
	{
		if (pair.second->getType() == "SpawnZone")
		{
			_initialEntitiesState[pair.first] = new SpawnZone(*static_cast<SpawnZone*>(pair.second), physSettings);
		}
	}

	// Create other components
	for (auto pair : initialEntitiesState)
	{
		if (pair.second->getType() == "Player")
		{
			auto player = static_cast<Player*>(pair.second);
			auto spawnGUID = static_cast<SpawnableComponent*>(player->getComponent(ComponentTypes::SpawnableComponent))->getCurrentSpawn()->getGUID();

			auto newSpawn = static_cast<SpawnZone*>(_initialEntitiesState[spawnGUID]);
			_initialEntitiesState[pair.first] = new Player(*static_cast<Player*>(pair.second), physSettings, newSpawn);
		}
		else if (pair.second->getType() == "StaticPlatform")
		{
			_initialEntitiesState[pair.first] = new StaticPlatform(*static_cast<StaticPlatform*>(pair.second), physSettings);
		}
		else if (pair.second->getType() == "PatternPlatform")
		{
			_initialEntitiesState[pair.first] = new PatternPlatform(*static_cast<PatternPlatform*>(pair.second), physSettings);
		}
		else if (pair.second->getType() == "DeathZone")
		{
			_initialEntitiesState[pair.first] = new DeathZone(*static_cast<DeathZone*>(pair.second), physSettings);
		}
		else if (pair.second->getType() == "SideBoundary")
		{
			_initialEntitiesState[pair.first] = new SideBoundary(*static_cast<SideBoundary*>(pair.second), physSettings);
		}
	}

	_replayTicks = std::queue<ReplayTick>();

	_initialGameTime = 0;
}

void Replay::addReplayTick(ReplayTick repTick)
{
	_replayTicks.emplace(repTick);
}

ReplayTick Replay::popReplayTick()
{
	auto tick = _replayTicks.front();
	_replayTicks.pop();
	return tick;
}
