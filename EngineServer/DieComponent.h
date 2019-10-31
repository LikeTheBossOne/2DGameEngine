#pragma once
#include "GenericComponent.h"

class DieComponent : public GenericComponent
{
public:
	DieComponent(GameObject* gameObject, bool canRespawn);
	DieComponent(GameObject* gameObject, bool canRespawn, GameObject* spawn);

	void onDie();

	void update(int deltaTime) override;
	ComponentTypes getType() override { return ComponentTypes::DieComponent; }

	void setCurrentSpawn(GameObject* spawn) { _currentSpawn = spawn; }
private:
	bool _canRespawn;

	GameObject* _currentSpawn;
};

