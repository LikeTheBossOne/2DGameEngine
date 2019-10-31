#pragma once
#include "GenericComponent.h"

class ColorComponent : public GenericComponent
{
public:
	ColorComponent(GameObject* gameObject, int r, int g, int b);

	void update(int deltaTime) override;
	ComponentTypes getType() override { return ComponentTypes::ColorComponent; }

	int getR() { return _r; }
	int getG() { return _g; }
	int getB() { return _b; }
private:
	int _r;
	int _g;
	int _b;
};

