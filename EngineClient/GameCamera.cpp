#include "GameCamera.h"

GameCamera::GameCamera(Game* game)
{
	_game = game;

	_attachedEntity = nullptr;

	_x = 0.f;
	_y = 0.f;
}

void GameCamera::attachToEntity(Entity* entity)
{
	_attachedEntity = entity;
}

float GameCamera::getX()
{
	return 0.f;
}

float GameCamera::getY()
{
	return 0.f;
}
