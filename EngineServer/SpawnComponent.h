#pragma once
#include "GenericComponent.h"

class SpawnComponent : public GenericComponent
{
public:
	SpawnComponent(GameObject* gameObject);

	void update(int deltaTime) override;
	ComponentTypes getType() override { return ComponentTypes::SpawnComponent; }
};

