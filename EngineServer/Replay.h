#pragma once
#include <map>
#include "ReplayTick.h"
#include <vector>
#include <queue>

class GameObject;
class PhysicsEngineSettings;

class Replay
{
public:
	Replay(std::map<int, GameObject*> initialEntitiesState, PhysicsEngineSettings* physSettings);

	void addReplayTick(ReplayTick repTick);
	ReplayTick popReplayTick();
	bool isEmpty() { return _replayTicks.empty(); }

	std::map<int, GameObject*> getInitialEntitiesState() { return _initialEntitiesState; }
private:
	std::map<int, GameObject*> _initialEntitiesState;

	std::queue<ReplayTick> _replayTicks;
	
	int _initialGameTime;
};

