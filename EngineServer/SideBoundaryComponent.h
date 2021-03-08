#pragma once
#include "GenericComponent.h"
class SideBoundaryComponent : public GenericComponent
{
public:
	SideBoundaryComponent(GameObject* gameObject, float sceneShiftWidth);
	SideBoundaryComponent(const SideBoundaryComponent& other, GameObject* gameObject);

	void update(int deltaTime) override;
	ComponentTypes getType() override { return ComponentTypes::SideBoundaryComponent; }

	float getSceneShiftWidth() { return _sceneShiftWidth; }
private:
	float _sceneShiftWidth;
};

