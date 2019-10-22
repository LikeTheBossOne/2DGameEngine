#include "CollisionsManager.h"
#include "GameObject.h"
#include "RectangleColliderComponent.h"
#include "RigidBodyComponent.h"
#include "MovementComponent.h"
#include "TransformComponent.h"
#include <iostream>
#include "JumpComponent.h"

CollisionsManager::CollisionsManager()
= default;

void CollisionsManager::update(std::map<int, GameObject*> entities, int totalEntitiesToDate)
{
	const float COLLISION_ERROR = 0.001f;
	
	std::vector<bool> hits(totalEntitiesToDate * totalEntitiesToDate, false);
	for (const std::pair<int, GameObject*> entitiesPair : entities)
	{
		for (const std::pair<int, GameObject*> oEntitiesPair : entities)
		{
			// Check if pair has already been collison-checked
			if (hits[entitiesPair.first * totalEntitiesToDate + oEntitiesPair.first]) continue;
			hits[entitiesPair.first * totalEntitiesToDate + oEntitiesPair.first] = true;

			if (entitiesPair.first == oEntitiesPair.first) continue;

			
			auto object1 = entitiesPair.second;
			auto object2 = oEntitiesPair.second;

			
			auto rigidBody1 = object1->getRigidBody();
			auto rigidBody2 = object2->getRigidBody();
			
			if (rigidBody1->isStatic() && rigidBody2->isStatic()) continue; // both static
			if (!rigidBody1->getCanPush() && !rigidBody2->getCanPush()) continue; // both can't push
			if (!rigidBody1->isPushable() && !rigidBody2->isPushable()) continue; // both can't be pushed


			auto transform1 = object1->getTransform();
			auto transform2 = object2->getTransform();
			
			
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
				const auto gMovement1 = object1->getComponent(ComponentTypes::MovementComponent);
				const bool canMove1 = gMovement1 != nullptr;
				auto movement1 = dynamic_cast<MovementComponent*>(gMovement1);

				const auto gMovement2 = object2->getComponent(ComponentTypes::MovementComponent);
				const bool canMove2 = gMovement1 != nullptr;
				auto movement2 = dynamic_cast<MovementComponent*>(gMovement2);
				
				// They both can push each other
				if (rigidBody1->isPushable() && rigidBody1->getCanPush() && rigidBody2->isPushable() && rigidBody2->
					getCanPush() && canMove1 && canMove2)
				{
					const float currX1 = collider1->getBounds().getX();
					const float currY1 = collider1->getBounds().getY();
					const float width1 = collider1->getBounds().getWidth();
					const float height1 = collider1->getBounds().getHeight();
					const float prevX1 = transform1->getPrevX() + collider1->getRelativeLeftBounds();
					const float prevY1 = transform1->getPrevY() + collider1->getRelativeTopBounds();
					const float currX2 = collider2->getBounds().getX();
					const float currY2 = collider2->getBounds().getY();
					const float width2 = collider2->getBounds().getWidth();
					const float height2 = collider2->getBounds().getHeight();
					const float prevX2 = transform2->getPrevX() + collider2->getRelativeLeftBounds();
					const float prevY2 = transform2->getPrevY() + collider2->getRelativeTopBounds();


					if (prevY1 + height1 <= prevY2 && currY1 + height1 > currY2) // 1 Can't go down
					{
						const float diffY = currY2 - (currY1 + height1);
						transform1->setPositionY(transform1->getPositionY() - COLLISION_ERROR + diffY / 2);
						transform2->setPositionY(transform2->getPositionY() + COLLISION_ERROR - diffY / 2);
						collider1->moveBounds(0, diffY / 2);
						collider2->moveBounds(0, -diffY / 2);
						movement1->setVelocityY(0);
						movement2->setVelocityY(0);

						const auto gJump1 = object1->getComponent(ComponentTypes::JumpComponent);
						if (gJump1 != nullptr)
						{
							dynamic_cast<JumpComponent*>(gJump1)->setIsJumping(false);
						}
					}
					if (prevY1 >= prevY2 + height2 && currY1 < currY2 + height2) // 1 Can't go up
					{
						const float diffY = (currY2 + height2) - currY1;
						transform1->setPositionY(transform1->getPositionY() + COLLISION_ERROR + diffY / 2);
						transform2->setPositionY(transform2->getPositionY() - COLLISION_ERROR - diffY / 2);
						collider1->moveBounds(0, diffY / 2);
						collider2->moveBounds(0, -diffY / 2);
						movement1->setVelocityY(0);
						movement2->setVelocityY(0);

						const auto gJump2 = object2->getComponent(ComponentTypes::JumpComponent);
						if (gJump2 != nullptr)
						{
							dynamic_cast<JumpComponent*>(gJump2)->setIsJumping(false);
						}
					}
					if (prevX1 + width1 <= prevX2 && currX1 + width1 > currX2) // 1 Can't go right
					{
						const float diffX = currX2 - (currX1 + height1);
						transform1->setPositionX(transform1->getPositionX() + diffX / 2);
						transform2->setPositionX(transform2->getPositionX() - diffX / 2);
						collider1->moveBounds(diffX / 2, 0);
						collider2->moveBounds(-diffX / 2, 0);
						movement1->setVelocityX(0);
						movement2->setVelocityX(0);
					}
					if (prevX1 >= prevX2 + width2 && currX1 < currX2 + width2) // Can't go left
					{
						const float diffX = (currX2 + width2) - currX1;
						transform1->setPositionX(transform1->getPositionX() + diffX / 2);
						transform2->setPositionX(transform2->getPositionX() - diffX / 2);
						collider1->moveBounds(diffX / 2, 0);
						collider2->moveBounds(-diffX / 2, 0);
						movement1->setVelocityX(0);
						movement2->setVelocityX(0);
					}
				}
				else if (rigidBody1->getCanPush() && rigidBody2->isPushable() && canMove2)
				{
					const float currX1 = collider1->getBounds().getX();
					const float currY1 = collider1->getBounds().getY();
					const float width1 = collider1->getBounds().getWidth();
					const float height1 = collider1->getBounds().getHeight();
					const float prevX1 = transform1->getPrevX() + collider1->getRelativeLeftBounds();
					const float prevY1 = transform1->getPrevY() + collider1->getRelativeTopBounds();
					const float currX2 = collider2->getBounds().getX();
					const float currY2 = collider2->getBounds().getY();
					const float width2 = collider2->getBounds().getWidth();
					const float height2 = collider2->getBounds().getHeight();
					const float prevX2 = transform2->getPrevX() + collider2->getRelativeLeftBounds();
					const float prevY2 = transform2->getPrevY() + collider2->getRelativeTopBounds();

					if (prevY1 + height1 <= prevY2 && currY1 + height1 > currY2) // 2 can't go up
					{
						const float diffY = (currY1 + height1) - currY2;
						transform2->setPositionY(transform2->getPositionY() + diffY + COLLISION_ERROR);
						collider2->moveBounds(0, diffY);
						movement2->setVelocityY(0);
					}
					if (prevY1 >= prevY2 + height2 && currY1 < currY2 + height2) // 2 can't go down
					{
						const float diffY = currY1 - (currY2 + height2);
						transform2->setPositionY(transform2->getPositionY() + diffY - COLLISION_ERROR);
						collider2->moveBounds(0, diffY);
						movement2->setVelocityY(0);

						auto gJump2 = object2->getComponent(ComponentTypes::JumpComponent);
						if (gJump2 != nullptr)
						{
							dynamic_cast<JumpComponent*>(gJump2)->setIsJumping(false);
						}
					}
					if (prevX1 + width1 <= prevX2 && currX1 + width1 > currX2) // 2 can't go left
					{
						const float diffX = (currX1 + width1) - currX2;
						transform2->setPositionX(transform2->getPositionX() + diffX);
						collider2->moveBounds(diffX, 0);
						movement2->setVelocityX(0);
					}
					if (prevX1 >= prevX2 + width2 && currX1 < currX2 + width2) // 2 can't go right
					{
						const float diffX = currX1 - (currX2 + width2);
						transform2->setPositionX(transform2->getPositionX() + diffX);
						collider2->moveBounds(diffX, 0);
						movement2->setVelocityX(0);
					}
				}
				else if (rigidBody2->getCanPush() && rigidBody1->isPushable() && canMove1)
				{
					const float currX1 = collider1->getBounds().getX();
					const float currY1 = collider1->getBounds().getY();
					const float width1 = collider1->getBounds().getWidth();
					const float height1 = collider1->getBounds().getHeight();
					const float prevX1 = transform1->getPrevX() + collider1->getRelativeLeftBounds();
					const float prevY1 = transform1->getPrevY() + collider1->getRelativeTopBounds();
					const float currX2 = collider2->getBounds().getX();
					const float currY2 = collider2->getBounds().getY();
					const float width2 = collider2->getBounds().getWidth();
					const float height2 = collider2->getBounds().getHeight();
					const float prevX2 = transform2->getPrevX() + collider2->getRelativeLeftBounds();
					const float prevY2 = transform2->getPrevY() + collider2->getRelativeTopBounds();

					if (prevY1 + height1 <= prevY2 && currY1 + height1 > currY2) // 1 Can't go down
					{
						const float diffY = currY2 - (currY1 + height1);
						transform1->setPositionY(transform1->getPositionY() + diffY - COLLISION_ERROR);
						collider1->moveBounds(0, diffY);
						movement1->setVelocityY(0);

						auto gJump1 = object1->getComponent(ComponentTypes::JumpComponent);
						if (gJump1 != nullptr)
						{
							dynamic_cast<JumpComponent*>(gJump1)->setIsJumping(false);
						}
					}
					if (prevY1 >= prevY2 + height2 && currY1 < currY2 + height2) // Can't go up
					{
						const float diffY = (currY2 + height2) - currY1;
						transform1->setPositionY(transform1->getPositionY() + diffY + COLLISION_ERROR);
						collider1->moveBounds(0, diffY);
						movement1->setVelocityY(0);
					}
					if (prevX1 + width1 <= prevX2 && currX1 + width1 > currX2) // Can't go right
					{
						const float diffX = currX2 - (currX1 + width1);
						transform1->setPositionX(transform1->getPositionX() + diffX);
						collider1->moveBounds(diffX, 0);
						movement1->setVelocityX(0);
					}
					if (prevX1 >= prevX2 + width2 && currX1 < currX2 + width2) // Can't go left
					{
						const float diffX = (currX2 + width2) - currX1;
						transform1->setPositionX(transform1->getPositionX() + diffX);
						collider1->moveBounds(diffX, 0);
						movement1->setVelocityX(0);
					}
				}
			}
		}
	}
}
