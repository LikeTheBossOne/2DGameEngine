#pragma once
#include <map>

class EventManager;
class GameObject;

class CollisionsDetector
{
public:
	CollisionsDetector();

	void update(std::map<int, GameObject*> entities, int totalEntitiesToDate);
private:
};
