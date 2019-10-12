#pragma once
class Entity;
class Game;

class GameCamera
{
public:
	GameCamera(Game* game);

	void attachToEntity(Entity* entity);
	float getX();
	float getY();
private:
	Game* _game;

	Entity* _attachedEntity;
	
	float _x;
	float _y;
};
