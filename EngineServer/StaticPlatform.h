#pragma once
#include "Entity.h"
#include "Platform.h"

class StaticPlatform : public Platform
{
public:
	StaticPlatform(Game* game, std::string textureName, float x, float y, float width, float height);
	StaticPlatform(Game* game, float x, float y, float width, float height);
	void tick(int deltaTime);
	// void draw();
	
};

