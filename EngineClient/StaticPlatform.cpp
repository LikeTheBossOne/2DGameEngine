#include "StaticPlatform.h"
#include "TransformComponent.h"

StaticPlatform::StaticPlatform(int GUID, sf::FloatRect location) : GameObject(GUID)
{
	_transform = new TransformComponent(this, location, true);

	_sfRectangleShape = new sf::RectangleShape(sf::Vector2f(location.width, location.height));
	_sfRectangleShape->setPosition(location.left, location.top);
}
