#pragma once
#include "Entity.h"
#include "Platform.h"

class DynamicPlatform : public Platform
{
public:
	DynamicPlatform(Game* game, std::string textureName, float x, float y, float width, float height);
	DynamicPlatform(Game* game, float x, float y, float width, float height);
	virtual void tick(int deltaTime);
	// virtual void draw();
	
	float getPrevX() { return _prevX; }
	float getPrevY() { return _prevY; }

	float getStartingX() { return _startingX; }
	float getStartingY() { return _startingY; }
protected:
	float _prevX;
	float _prevY;

	float _startingX;
	float _startingY;
};

