#pragma once
#include "Entity.h"

namespace sf {
	class Texture;
}

class Platform : public Entity
{
public:
	Platform(Game* game, std::string textureName, float x, float y, float width, float height);
	Platform(Game* game, float x, float y, float width, float height);
	virtual void tick(int deltaTime);

	virtual float getCurrentVelocityX() { return 0; }
	virtual float getCurrentVelocityY() { return 0; }
};

