#include "SpawnComponent.h"

SpawnComponent::SpawnComponent(GameObject* gameObject) : GenericComponent(gameObject)
{
}

SpawnComponent::SpawnComponent(const SpawnComponent& other, GameObject* gameObject) : GenericComponent(gameObject)
{
	
}

void SpawnComponent::update(int deltaTime)
{
}
