#pragma once
#include "Entity.h"
#include "Platform.h"

class DynamicPlatform : public Platform
{
public:
	DynamicPlatform(Game* game, sf::Texture* texture, sf::Vector2f location, sf::Vector2f size);
	DynamicPlatform(Game* game, sf::Vector2f location, sf::Vector2f size);
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

