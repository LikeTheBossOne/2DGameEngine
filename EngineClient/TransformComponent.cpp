#include "TransformComponent.h"

TransformComponent::TransformComponent(GameObject* gameObject, sf::FloatRect position) : GenericComponent(gameObject)
{
	_position = position;
}

