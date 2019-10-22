#include "TransformComponent.h"
#include "MovementComponent.h"

TransformComponent::TransformComponent(GameObject* gameObject, Rect position) : GenericComponent(gameObject)
{	
	_position = position;

	_prevX = position.getX();
	_prevY = position.getY();
}

void TransformComponent::update(int deltaTime)
{
	_prevX = _position.getX();
	_prevY = _position.getY();
}
