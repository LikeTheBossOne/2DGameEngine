#pragma once
class EntityRectangle
{
public:
	EntityRectangle();
	EntityRectangle(float x, float y, float width, float height);
	EntityRectangle(float width, float height);

	virtual ~EntityRectangle() = default;

	void move(float x, float y);
	void setPosition(float x, float y);

	bool intersects(EntityRectangle& otherRect, EntityRectangle& intersection);
	
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

