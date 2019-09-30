#include "Platform.h"

Platform::Platform(Game* game, std::string textureName, float x, float y, float width, float height) : Entity(game, textureName, x, y, width, height)
{
}

Platform::Platform(Game* game, float x, float y, float width, float height) : Entity(game, x, y, width, height)
{
}

void Platform::tick(int deltaTime)
{
	
}
