#pragma once
#include "GenericComponent.h"

class DieComponent : public GenericComponent
{
public:
	DieComponent(GameObject* gameObject, bool canRespawn);
	DieComponent(const DieComponent& other, GameObject* gameObject);

	void update(int deltaTime) override;

	bool canRespawn() { return _canRespawn; }
	ComponentTypes getType() override { return ComponentTypes::DieComponent; }
private:
	bool _canRespawn;
};

