#include "DieComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"

DieComponent::DieComponent(GameObject* gameObject, bool canRespawn) : GenericComponent(gameObject)
{
	_canRespawn = canRespawn;
	_currentSpawn = nullptr;
}

DieComponent::DieComponent(GameObject* gameObject, bool canRespawn, GameObject* spawn) : GenericComponent(gameObject)
{
	_canRespawn = canRespawn;
	_currentSpawn = spawn;
}

void DieComponent::onDie()
{
	if (_currentSpawn != nullptr)
	{
		_gameObject->getTransform()->setPositionX(_currentSpawn->getTransform()->getPositionX());
		_gameObject->getTransform()->setPositionY(_currentSpawn->getTransform()->getPositionY());
	}
}

void DieComponent::update(int deltaTime)
{
}
