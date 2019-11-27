#pragma once
#include "GenericComponent.h"

class SpawnableComponent : public GenericComponent
{
public:
	SpawnableComponent(GameObject* gameObject);
	SpawnableComponent(GameObject* gameObject, GameObject* spawn);
	SpawnableComponent(const SpawnableComponent& other, GameObject* gameObject, GameObject* spawn);

	void update(int deltaTime) override;

	void setCurrentSpawn(GameObject* spawn) { _currentSpawn = spawn; }

	GameObject* getCurrentSpawn() { return _currentSpawn; }
	ComponentTypes getType() override { return ComponentTypes::SpawnableComponent; }
private:
	GameObject* _currentSpawn;
};

