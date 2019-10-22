#pragma once
#include <map>

class GameObject;

class CollisionsManager
{
public:
	CollisionsManager();

	void update(std::map<int, GameObject*> entities, int totalEntitiesToDate);
};
