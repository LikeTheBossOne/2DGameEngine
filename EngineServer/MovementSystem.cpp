#include "MovementSystem.h"
#include "Event.h"
#include "CollisionEvent.h"
#include "GameObject.h"
#include "RectangleColliderComponent.h"
#include "MovementComponent.h"
#include "TransformComponent.h"
#include "JumpComponent.h"
#include "EventManager.h"
#include "DieComponent.h"
#include "RigidBodyComponent.h"
#include "SpawnEvent.h"
#include "SpawnableComponent.h"

MovementSystem::MovementSystem()
{
	EventManager::getInstance()->registerFor(this, "Col");
	EventManager::getInstance()->registerFor(this, "Spawn");
}

void MovementSystem::onEvent(Event* e)
{
	if (e->getType() == "Col")
	{
		handleBothMovableCollision(static_cast<CollisionEvent*>(e));
	}
	else if (e->getType() == "Spawn")
	{
		handleSpawn(static_cast<SpawnEvent*>(e));
	}

}

void MovementSystem::handleBothMovableCollision(CollisionEvent* e)
{
	const float COLLISION_ERROR = 0.001f;
	
	auto object1 = e->first;
	auto object2 = e->second;

	auto transform1 = object1->getTransform();
	auto transform2 = object2->getTransform();
	
	auto rigidBody1 = object1->getRigidBody();
	auto rigidBody2 = object2->getRigidBody();

	auto collider1 = static_cast<RectangleColliderComponent*>(object1->getComponent(ComponentTypes::RectangleColliderComponent));
	auto collider2 = static_cast<RectangleColliderComponent*>(object2->getComponent(ComponentTypes::RectangleColliderComponent));
	
	// Check Movement Components
	const auto gMovement1 = object1->getComponent(ComponentTypes::MovementComponent);
	const bool canMove1 = gMovement1 != nullptr;
	auto movement1 = static_cast<MovementComponent*>(gMovement1);

	const auto gMovement2 = object2->getComponent(ComponentTypes::MovementComponent);
	const bool canMove2 = gMovement1 != nullptr;
	auto movement2 = static_cast<MovementComponent*>(gMovement2);

	// Skip if non-pushers
	if (!rigidBody1->getCanPush() && !rigidBody2->getCanPush()) return; // both can't push
	if (!rigidBody1->isPushable() && !rigidBody2->isPushable()) return; // both can't be pushed


	// Now we Handle Collision
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
				static_cast<JumpComponent*>(gJump1)->setIsJumping(false);
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
				static_cast<JumpComponent*>(gJump2)->setIsJumping(false);
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

			const auto gJump2 = object2->getComponent(ComponentTypes::JumpComponent);
			if (gJump2 != nullptr)
			{
				static_cast<JumpComponent*>(gJump2)->setIsJumping(false);
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

			const auto gJump1 = object1->getComponent(ComponentTypes::JumpComponent);
			if (gJump1 != nullptr)
			{
				static_cast<JumpComponent*>(gJump1)->setIsJumping(false);
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

void MovementSystem::handleSpawn(SpawnEvent* e)
{	
	auto object = e->spawningObject;

	// Check if has spawnable component
	const auto gSpawnable = object->getComponent(ComponentTypes::SpawnableComponent);
	if (gSpawnable != nullptr)
	{
		auto spawnable = static_cast<SpawnableComponent*>(gSpawnable);
		object->getTransform()->setPositionX(spawnable->getCurrentSpawn()->getTransform()->getPositionX());
		object->getTransform()->setPositionY(spawnable->getCurrentSpawn()->getTransform()->getPositionY());


		const auto gMovement = object->getComponent(ComponentTypes::MovementComponent);
		if (gMovement != nullptr)
		{
			auto movement = static_cast<MovementComponent*>(gMovement);

			// static_cast<DieComponent*>(gDie2)->onDie();

			movement->setVelocityX(0);
			movement->setVelocityY(0);
		}
	}
	
}
