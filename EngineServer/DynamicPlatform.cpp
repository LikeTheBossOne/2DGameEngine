#include "DynamicPlatform.h"

DynamicPlatform::DynamicPlatform(Game* game, std::string textureName, float x, float y, float width, float height) : Platform(game, textureName, x, y, width, height)
{
	_prevX = x;
	_prevY = y;

	_startingX = x;
	_startingY = y;
}

DynamicPlatform::DynamicPlatform(Game* game, float x, float y, float width, float height) : Platform(game, x, y, width, height)
{
	_prevX = x;
	_prevY = y;

	_startingX = x;
	_startingY = y;
}

void DynamicPlatform::tick(int deltaTime)
{
	// TODO: tick
}
