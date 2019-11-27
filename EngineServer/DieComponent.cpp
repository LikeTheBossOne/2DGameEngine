#include "DieComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"

DieComponent::DieComponent(GameObject* gameObject, bool canRespawn) : GenericComponent(gameObject)
{
	_canRespawn = canRespawn;
}

DieComponent::DieComponent(const DieComponent& other, GameObject* gameObject) : GenericComponent(gameObject)
{
	_canRespawn = other._canRespawn;
}

void DieComponent::update(int deltaTime)
{
}
