#include "StaticPlatform.h"

StaticPlatform::StaticPlatform(Game* game, std::string textureName, float x, float y, float width, float height) : Platform(game, textureName, x, y, width, height)
{
}

StaticPlatform::StaticPlatform(Game* game, float x, float y, float width, float height) : Platform(game, x, y, width, height)
{
}

void StaticPlatform::tick(int deltaTime)
{
}
