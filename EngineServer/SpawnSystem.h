#pragma once
#include "EventHandler.h"
class DeathEvent;

class SpawnSystem : public EventHandler
{
public:
	static bool scriptInitialized;
	
	SpawnSystem();
	void onEvent(Event* e) override;

	void handleDeath(DeathEvent* e);
};

