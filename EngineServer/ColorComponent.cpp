#include "ColorComponent.h"

ColorComponent::ColorComponent(GameObject* gameObject, int r, int g, int b) : GenericComponent(gameObject)
{
	_r = r;
	_g = g;
	_b = b;
}

ColorComponent::ColorComponent(const ColorComponent& other, GameObject* gameObject) : GenericComponent(gameObject)
{
	_r = other._r;
	_g = other._g;
	_b = other._b;
}

void ColorComponent::update(int deltaTime)
{
}
