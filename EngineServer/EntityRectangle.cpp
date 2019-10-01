#include "EntityRectangle.h"
#include <algorithm>

EntityRectangle::EntityRectangle()
{
	_x = 0;
	_y = 0;
	_width = 0;
	_height = 0;
}

EntityRectangle::EntityRectangle(float x, float y, float width, float height)
{
	_x = x;
	_y = y;
	_width = width;
	_height = height;
}

EntityRectangle::EntityRectangle(float width, float height)
{
	_x = 0;
	_y = 0;
	_width = width;
	_height = height;
}

void EntityRectangle::move(float x, float y)
{
	_x += x;
	_y += y;
}

void EntityRectangle::setPosition(float x, float y)
{
	_x = x;
	_y = y;
}

bool EntityRectangle::intersects(EntityRectangle& otherRect, EntityRectangle& intersection)
{
	// Compute the min and max of the first rectangle on both axes
	const float r1MinX = std::min(_x, _x + _width);
	const float r1MaxX = std::max(_x, _x + _width);
	const float r1MinY = std::min(_y, _y + _height);
	const float r1MaxY = std::max(_y, _y + _height);

	// Compute the min and max of the second rectangle on both axes
	const float r2MinX = std::min(otherRect.getX(), otherRect.getX() + otherRect.getWidth());
	const float r2MaxX = std::max(otherRect.getX(), otherRect.getX() + otherRect.getWidth());
	const float r2MinY = std::min(otherRect.getY(), otherRect.getY() + otherRect.getHeight());
	const float r2MaxY = std::max(otherRect.getY(), otherRect.getY() + otherRect.getHeight());

	// Compute the floatersection boundaries
	const float interLeft = std::max(r1MinX, r2MinX);
	const float interin_y = std::max(r1MinY, r2MinY);
	const float interRight = std::min(r1MaxX, r2MaxX);
	const float interBottom = std::min(r1MaxY, r2MaxY);

	// If the intersection is valid (positive non zero area), then there is an intersection
	if ((interLeft < interRight) && (interin_y < interBottom))
	{
		intersection = EntityRectangle(interLeft, interin_y, interRight - interLeft, interBottom - interin_y);
		return true;
	}
	else
	{
		intersection = EntityRectangle(0, 0, 0, 0);
		return false;
	}
}
