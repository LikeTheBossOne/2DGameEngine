#include "RectangleColliderComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"

/**
 * The relative bounds define how much the collider cuts in to the bounds of a transform.
 * A positive number indicates a smaller bounds than transform
 */
RectangleColliderComponent::RectangleColliderComponent(GameObject* gameObject, float relativeLeft, float relativeTop,
	float width, float height) : GenericComponent(gameObject)
{
	auto transform = _gameObject->getTransform();
	_relativeLeftBounds = relativeLeft;
	_relativeTopBounds = relativeTop;
	_bounds = EngineRectangle(Rect(transform->getPositionX() + relativeLeft, transform->getPositionY() + relativeTop, width, height));
}


void RectangleColliderComponent::update(int deltaTime)
{
	auto transform = _gameObject->getTransform();

	_bounds.setPosition(transform->getPositionX() + _relativeLeftBounds, transform->getPositionY() + _relativeTopBounds);
}

void RectangleColliderComponent::setBounds(float x, float y)
{
	_bounds.setPosition(x, y);
}

void RectangleColliderComponent::moveBounds(float x, float y)
{
	_bounds.setPosition(_bounds.getX() + x, _bounds.getY() + y);
}
