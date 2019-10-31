#pragma once
#include "Rect.h"

class EngineRectangle
{
public:
	EngineRectangle();
	EngineRectangle(Rect rect);
	EngineRectangle(float width, float height);

	virtual ~EngineRectangle() = default;

	void move(float x, float y);
	void setPosition(float x, float y);

	bool intersects(EngineRectangle otherRect, EngineRectangle& intersection);
	
	float getX() { return _rect.getX(); }
	float getY() { return _rect.getY();}
	float getWidth() { return _rect.getWidth(); }
	float getHeight() { return _rect.getHeight(); }
private:
	Rect _rect;
};

