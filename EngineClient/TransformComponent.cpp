#include "TransformComponent.h"

TransformComponent::TransformComponent(GameObject* gameObject, sf::FloatRect position, bool isVisible) : GenericComponent(gameObject)
{
	_position = position;
	_isVisible = isVisible;
}

void TransformComponent::update(int deltaTime)
{
	
}


