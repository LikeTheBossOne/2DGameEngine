#include "Entity.h"

int Entity::nextId = 0;

Entity::Entity(Game* game, std::string textureName, float x, float y, float width, float height) : EntityRectangle(x, y, width, height)
{
	_game = game;
	_textureName = textureName;
	_GUID = nextId;
	_textureRect = nullptr;
	
	nextId++;
}

Entity::Entity(Game* game, float x, float y, float width, float height) : EntityRectangle(x, y, width, height)
{
	_game = game;
	_textureName = "";
	_GUID = nextId;
	_textureRect = nullptr;

	nextId++;
}
