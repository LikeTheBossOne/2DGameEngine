#pragma once
#include "EntityRectangle.h"
#include <string>

namespace sf {
	class Time;
}
class Game;

class Entity : public EntityRectangle
{
public:
	Entity(Game* game, std::string textureName, float x, float y, float width, float height);
	Entity(Game* game, float x, float y, float width, float height);
	virtual void tick(int deltaTime) = 0;

	void setTextureName(std::string textureName) { _textureName = textureName; }
	void setTextureRect(EntityRectangle* rect) { _textureRect = rect; };

	std::string getTextureName() { return _textureName; }
	EntityRectangle* getTextureRect() { return _textureRect; }
	
	int getGUID() { return _GUID; }

protected:
	Game* _game;
private:
	int _GUID;
	static int nextId;

	std::string _textureName;
	EntityRectangle* _textureRect;
};

