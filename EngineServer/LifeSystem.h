#pragma once
#include "EventHandler.h"
class DeathEvent;
class CollisionEvent;

class LifeSystem : public EventHandler
{
public:
	static bool scriptInitialized;
	
	LifeSystem();
	void onEvent(Event* e) override;

	void handleCollision(CollisionEvent* e);
};

