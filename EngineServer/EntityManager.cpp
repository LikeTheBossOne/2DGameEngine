#include "EntityManager.h"
#include "Game.h"
#include "GameObject.h"
#include "PhysicsEngineSettings.h"
#include "GenericComponent.h"
#include "RigidBodyComponent.h"
#include "CollisionsManager.h"
#include "TransformComponent.h"
#include "MovementComponent.h"
#include <iostream>
#include "SpawnZone.h"

EntityManager::EntityManager(Game* game)
{
	_game = game;

	_collisionsManager = new CollisionsManager();
	
	// Initialize Physics Engine
	_physicsEngineSettings = new PhysicsEngineSettings();
	_physicsEngineSettings->setGravityX(0);
	_physicsEngineSettings->setGravityY(-0.01);
	_physicsEngineSettings->setMaxSpeed(100);

	_entities = std::map<int, GameObject*>();
	_totalEntitiesToDate = 0;

	_spawns = std::vector<SpawnZone*>();
}

void EntityManager::addEntity(GameObject* entity)
{
	_entitiesLock.lock();
	
	_entities.emplace(entity->getGUID(), entity);

	_totalEntitiesToDate++;

	_entitiesLock.unlock();
}

void EntityManager::deleteEntity(int GUID)
{
	_entitiesLock.lock();
	
	_entities.erase(GUID);

	_entitiesLock.unlock();
}

void EntityManager::addSpawn(SpawnZone* spawn)
{
	_spawns.emplace_back(spawn);
}

std::map<int, GameObject*> EntityManager::getEntities()
{
	std::lock_guard<std::mutex> lg(_entitiesLock);
	return _entities;
}

/**
 * Update Entities then Player
 */
void EntityManager::update(int deltaTime)
{
	// Grab current entities so nothing changes (multithreading) during the update process.
	_entitiesLock.lock();
	auto currentEntities = _entities;
	auto totalEntities = _totalEntitiesToDate;
	_entitiesLock.unlock();

	for (const std::pair<int, GameObject*> entity : currentEntities)
	{
		auto object = entity.second;
		
		// Update prevX and prevY
		auto gComponent = object->getComponent(ComponentTypes::PlayerInputComponent);
		if (gComponent != nullptr)
		{
			gComponent->update(deltaTime);
		}
	}
	
	// Update all entities that can't stick to a surface
	for (const std::pair<int, GameObject*> entity : currentEntities)
	{
		auto object = entity.second;
		if (!object->getRigidBody()->getCanStickToSurface())
		{
			// Update prevX and prevY
			TransformComponent* transform = object->getTransform();
			transform->update(deltaTime);
			
			// Let RigidBodyComponent set MovementComponent (Gravity)
			RigidBodyComponent* rigidBody = object->getRigidBody();
			rigidBody->update(deltaTime);

			// Let JumpComponent set MovementComponent
			auto gComponent = object->getComponent(ComponentTypes::JumpComponent);
			if (gComponent != nullptr)
			{
				gComponent->update(deltaTime);
			}
			
			// Let PatternComponent set MovementComponent
			gComponent = object->getComponent(ComponentTypes::PatternComponent);
			if (gComponent != nullptr)
			{
				gComponent->update(deltaTime);
			}

			// Let MovementComponent set TransformComponent
			gComponent = object->getComponent(ComponentTypes::MovementComponent);
			if (gComponent != nullptr)
			{
				gComponent->update(deltaTime);
			}

			// Do Collider last because it is based on delta between prev transform and current
			gComponent = object->getComponent(ComponentTypes::RectangleColliderComponent);
			if (gComponent != nullptr)
			{
				gComponent->update(deltaTime);
			}
		}
	}

	
	// Update Movement based on surface stick if entity can stick to surface
	for (const std::pair<int, GameObject*> entity : currentEntities)
	{
		auto object = entity.second;
		if (object->getRigidBody()->getCanStickToSurface())
		{
			// Update prevX and prevY
			TransformComponent* transform = object->getTransform();
			transform->update(deltaTime);

			// Let RigidBodyComponent set MovementComponent (Gravity)
			RigidBodyComponent* rigidBody = object->getRigidBody();
			rigidBody->update(deltaTime);
		}
	}
	
	// Update Position based on Movement for entities that can stick to surface
	for (const std::pair<int, GameObject*> entity : currentEntities)
	{
		auto object = entity.second;
		if (object->getRigidBody()->getCanStickToSurface())
		{
			// Let JumpComponent set MovementComponent
			auto gComponent = object->getComponent(ComponentTypes::JumpComponent);
			if (gComponent != nullptr)
			{
				gComponent->update(deltaTime);
			}
			
			// Let PatternComponent set MovementComponent
			gComponent = object->getComponent(ComponentTypes::PatternComponent);
			if (gComponent != nullptr)
			{
				gComponent->update(deltaTime);
			}

			// Let MovementComponent set TransformComponent
			gComponent = object->getComponent(ComponentTypes::MovementComponent);
			if (gComponent != nullptr)
			{
				gComponent->update(deltaTime);
			}

			// Do Collider last because it is based on delta between prev transform and current
			gComponent = object->getComponent(ComponentTypes::RectangleColliderComponent);
			if (gComponent != nullptr)
			{
				gComponent->update(deltaTime);
			}
		}
	}

	// Do physics/collisions
	_collisionsManager->update(currentEntities, totalEntities);

	// Update Textures
}
