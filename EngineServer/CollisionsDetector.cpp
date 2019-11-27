#include "CollisionsDetector.h"
#include "GameObject.h"
#include "RectangleColliderComponent.h"
#include "RigidBodyComponent.h"
#include "MovementComponent.h"
#include "TransformComponent.h"
#include <iostream>
#include "JumpComponent.h"
#include "DieComponent.h"
#include "EventManager.h"
#include "CollisionEvent.h"

CollisionsDetector::CollisionsDetector() = default;

void CollisionsDetector::update(std::map<int, GameObject*> entities, int totalEntitiesToDate)
{
	const float COLLISION_ERROR = 0.001f;
	
	std::vector<bool> hits(totalEntitiesToDate * totalEntitiesToDate, false);
	for (const std::pair<int, GameObject*> entitiesPair : entities)
	{
		// if it ignores collisions skip it.
		if (entitiesPair.second->getRigidBody()->getIgnoreCollisions()) continue;
		
		for (const std::pair<int, GameObject*> oEntitiesPair : entities)
		{
			// if it ignores collisions skip it.
			if (oEntitiesPair.second->getRigidBody()->getIgnoreCollisions()) continue;
			
			// Check if pair has already been collison-checked
			if (hits[entitiesPair.first * totalEntitiesToDate + oEntitiesPair.first]) continue;
			hits[entitiesPair.first * totalEntitiesToDate + oEntitiesPair.first] = true;

			if (entitiesPair.first == oEntitiesPair.first) continue;

			
			auto object1 = entitiesPair.second;
			auto object2 = oEntitiesPair.second;

			
			auto rigidBody1 = object1->getRigidBody();
			auto rigidBody2 = object2->getRigidBody();
			
			if (rigidBody1->isStatic() && rigidBody2->isStatic()) continue; // both static
			
			
			const auto gCollider1 = object1->getComponent(ComponentTypes::RectangleColliderComponent);
			if (gCollider1 == nullptr) continue;
			auto collider1 = dynamic_cast<RectangleColliderComponent*>(gCollider1);

			const auto gCollider2 = object2->getComponent(ComponentTypes::RectangleColliderComponent);
			if (gCollider2 == nullptr) continue;
			auto collider2 = dynamic_cast<RectangleColliderComponent*>(gCollider2);

			
			// Check if collision
			EngineRectangle collisionRect;
			if (collider1->getBounds().intersects(collider2->getBounds(), collisionRect))
			{
				auto collision = new CollisionEvent(object1, object2);
				EventManager::getInstance()->raiseEvent(collision);
			}
		}
	}
}
