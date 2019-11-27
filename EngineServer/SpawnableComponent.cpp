#include "SpawnableComponent.h"

SpawnableComponent::SpawnableComponent(GameObject* gameObject) : GenericComponent(gameObject)
{
	_currentSpawn = nullptr;
}

SpawnableComponent::SpawnableComponent(GameObject* gameObject, GameObject* spawn) : GenericComponent(gameObject)
{
	_currentSpawn = spawn;
}

SpawnableComponent::SpawnableComponent(const SpawnableComponent& other, GameObject* gameObject, GameObject* spawn) : GenericComponent(gameObject)
{
	_currentSpawn = spawn;
}

void SpawnableComponent::update(int deltaTime)
{
}
