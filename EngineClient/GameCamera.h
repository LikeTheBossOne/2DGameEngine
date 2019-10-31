#pragma once
class Entity;
class Game;

class GameCamera
{
public:
	GameCamera();

	void setOffsetX(float offsetX) { _offsetX = offsetX; }
	void setOffsetY(float offsetY) { _offsetY = offsetY; }
	void move(float x, float y);
	
	float getOffsetX() { return _offsetX; }
	float getOffsetY() { return _offsetY; }
private:
	
	float _offsetX;
	float _offsetY;
};
