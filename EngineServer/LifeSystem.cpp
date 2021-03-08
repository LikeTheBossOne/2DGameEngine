#include "LifeSystem.h"
#include "EventManager.h"
#include "CollisionEvent.h"
#include "ComponentTypes.h"
#include "GameObject.h"
#include "KillComponent.h"
#include "DieComponent.h"
#include "MovementComponent.h"
#include "DeathEvent.h"
#include "ScriptManager.h"
#include <dukglue/dukglue.h>

bool LifeSystem::scriptInitialized = false;

LifeSystem::LifeSystem()
{
	if (!scriptInitialized)
	{
		// duk_context* ctx = ScriptManager::getInstance()->getContext();
		// dukglue_register_property<DeathEvent, GameObject*>(ctx, &DeathEvent::getDyingObject, &DeathEvent::setDyingObject, "dyingObject");
		
		scriptInitialized = true;
	}
	EventManager::getInstance()->registerFor(this, "Col");
}

void LifeSystem::onEvent(Event* e)
{
	if (e->getType() == "Col")
	{
		handleCollision(static_cast<CollisionEvent*>(e));
	}
}

void LifeSystem::handleCollision(CollisionEvent* e)
{
	auto object1 = e->first;
	auto object2 = e->second;
	
	// First check if Killer Object
	const auto gKill1 = object1->getComponent(ComponentTypes::KillComponent);
	const auto gKill2 = object2->getComponent(ComponentTypes::KillComponent);
	const auto gDie1 = object1->getComponent(ComponentTypes::DieComponent);
	const auto gDie2 = object2->getComponent(ComponentTypes::DieComponent);
	if (gKill1 != nullptr && gDie2 != nullptr)
	{
		auto death = new DeathEvent(object2);
		EventManager::getInstance()->raiseEvent(death);
	}
	if (gKill2 != nullptr && gDie1 != nullptr)
	{
		auto death = new DeathEvent(object1);
		EventManager::getInstance()->raiseEvent(death);
	}
}
