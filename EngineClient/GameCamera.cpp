#include "GameCamera.h"

GameCamera::GameCamera(Game* game)
{
	_game = game;
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
