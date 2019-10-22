#include "ColorComponent.h"

ColorComponent::ColorComponent(GameObject* gameObject, int r, int g, int b) : GenericComponent(gameObject)
{
	_r = r;
	_g = g;
	_b = b;
}

void ColorComponent::update(int deltaTime)
{
}