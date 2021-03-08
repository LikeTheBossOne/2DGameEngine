#pragma once
#include "EventHandler.h"

class SpawnEvent;
class CollisionEvent;

class MovementSystem : public EventHandler
{
public:
	MovementSystem();
	void onEvent(Event* e) override;
	
private:
	void handleBothMovableCollision(CollisionEvent* e);
	void handleSpawn(SpawnEvent* e);
	
};

