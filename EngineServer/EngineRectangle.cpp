#include "EngineRectangle.h"
#include <algorithm>

EngineRectangle::EngineRectangle()
{
	_rect = Rect(0, 0, 0, 0);
}

EngineRectangle::EngineRectangle(Rect rect)
{
	_rect = rect;
}

EngineRectangle::EngineRectangle(float width, float height)
{
	_rect = Rect(0, 0, width, height);
}

void EngineRectangle::move(float x, float y)
{
	_rect.setX(_rect.getX() + x);
	_rect.setY(_rect.getY() + y);
}

void EngineRectangle::setPosition(float x, float y)
{
	_rect.setX(x);
	_rect.setY(y);
}

bool EngineRectangle::intersects(EngineRectangle otherRect, EngineRectangle& intersection)
{
	// Compute the min and max of the first rectangle on both axes
	const float r1MinX = std::min(getX(), getX() + getWidth());
	const float r1MaxX = std::max(getX(), getX() + getWidth());
	const float r1MinY = std::min(getY(), getY() + getHeight());
	const float r1MaxY = std::max(getY(), getY() + getHeight());

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
		intersection = EngineRectangle(Rect(interLeft, interin_y, interRight - interLeft, interBottom - interin_y));
		return true;
	}
	else
	{
		intersection = EngineRectangle(Rect(0, 0, 0, 0));
		return false;
	}
}
