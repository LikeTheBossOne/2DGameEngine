#include "SpawnSystem.h"
#include "EventManager.h"
#include "DeathEvent.h"
#include "DieComponent.h"
#include "GameObject.h"
#include "MovementComponent.h"
#include "SpawnEvent.h"
#include "ScriptManager.h"
#include <dukglue/dukglue.h>
#include "DeathEventParameter.h"
#include "EventManagerParameter.h"
#include <iostream>
#include "Player.h"

bool SpawnSystem::scriptInitialized = false;

SpawnSystem::SpawnSystem()
{
	if (!scriptInitialized)
	{
		ScriptManager::getInstance()->registerScript("SpawnSystem.handleDeath", "scripts/SpawnSystem.js", "handleDeath");

		// duk_context* ctx = ScriptManager::getInstance()->getContext();
		// dukglue_register_constructor<SpawnEvent, Player*>(ctx, "SpawnEvent");
		
		scriptInitialized = true;
	}
	EventManager::getInstance()->registerFor(this, "Death");
}

void SpawnSystem::onEvent(Event* e)
{
	if (e->getType() == "Death")
	{
		handleDeath(static_cast<DeathEvent*>(e));
	}
}

void SpawnSystem::handleDeath(DeathEvent* e)
{
	DeathEventParameter deathEventParam(e);
	EventManagerParameter eventManagerParam(EventManager::getInstance());
	
	std::vector<Parameter*> sParams;
	sParams.emplace_back(&deathEventParam);
	sParams.emplace_back(&eventManagerParam);
	
	ScriptReturnValue retVal(ParameterType::NONE);

	duk_context* ctx = duk_create_heap_default();
	dukglue_set_base_class<GameObject, Player>(ctx);
	dukglue_set_base_class<Event, SpawnEvent>(ctx);
	dukglue_register_constructor<SpawnEvent, GameObject*>(ctx, "SpawnEvent");
	dukglue_register_property<DeathEvent, GameObject*>(ctx, &DeathEvent::getDyingObject, &DeathEvent::setDyingObject, "dyingObject");
	dukglue_register_method(ctx, &EventManager::raiseEvent, "raiseEvent");
	ScriptManager::getInstance()->run("SpawnSystem.handleDeath", sParams, &retVal, ctx);
	duk_destroy_heap(ctx);
	
	// auto object = e->getDyingObject();
	//
	// auto spawn = new SpawnEvent(object);
	// EventManager::getInstance()->raiseEvent(spawn);
}
