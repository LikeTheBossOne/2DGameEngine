#pragma once
class Rect
{
public:
	Rect();
	Rect(float x, float y, float width, float height);

	void setX(float x) { _x = x; }
	void setY(float y) { _y = y; }
	void setWidth(float width) { _width = width; }
	void setHeight(float height) { _height = height; }
	
	float getX() { return _x; }
	float getY() { return _y; }
	float getWidth() { return _width; }
	float getHeight() { return _height; }
private:
	float _x;
	float _y;
	float _width;
	float _height;
};

