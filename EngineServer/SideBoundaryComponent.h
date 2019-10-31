#pragma once
#include "GenericComponent.h"
class SideBoundaryComponent : public GenericComponent
{
public:
	SideBoundaryComponent(GameObject* gameObject, float sceneShiftWidth);

	void update(int deltaTime) override;
	ComponentTypes getType() override { return ComponentTypes::SideBoundaryComponent; }

	float getSceneShiftWidth() { return _sceneShiftWidth; }
private:
	float _sceneShiftWidth;
};

