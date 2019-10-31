#pragma once
#include "GenericComponent.h"

class KillComponent : public GenericComponent
{
public:
	KillComponent(GameObject* gameObject);

	void update(int deltaTime) override;
	ComponentTypes getType() override { return ComponentTypes::KillComponent; }
};

