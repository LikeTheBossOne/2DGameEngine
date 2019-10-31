#include "GameCamera.h"

GameCamera::GameCamera()
{
	_offsetX = 0;
	_offsetY = 0;
}

void GameCamera::move(float x, float y)
{
	_offsetX += x;
	_offsetY += y;
}
