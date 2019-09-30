#pragma once
#include "Entity.h"
#include "Orientation.h"
#include <string>

class Platform;

class Player: public Entity
{
public:
	Player(Game* game, std::string textureName, float x, float y, float width, float height);
	Player(Game* game, float x, float y, float width, float height);
	virtual ~Player();

	void tick(int deltaTime) override;
private:
	float _velocityX;
	float _velocityY;
	float _accelerationX;
	float _accelerationY;

	Platform* _groundPlat;

	Orientation _orientation;
};

