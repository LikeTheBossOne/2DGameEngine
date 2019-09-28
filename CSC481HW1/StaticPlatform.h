#pragma once
#include "Entity.h"
#include "Platform.h"

class StaticPlatform : public Platform
{
public:
	StaticPlatform(Game* game, sf::Texture* texture, sf::Vector2f location, sf::Vector2f size);
	StaticPlatform(Game* game, sf::Vector2f location, sf::Vector2f size);
	void tick(int deltaTime);
	// void draw();
	
};

