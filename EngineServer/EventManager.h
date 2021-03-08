#pragma once
#include <queue>
#include <string>
#include <unordered_map>
#include "Event.h"
#include <mutex>

class SpawnEvent;
class Timeline;
class EventHandler;

struct EventCompare
{
	bool operator()(Event* lhs, Event* rhs)
	{
		if (lhs->getToHandleTimestamp() == rhs->getToHandleTimestamp())
		{
			return lhs->getPriority() < rhs->getPriority();
		}
		return (lhs->getToHandleTimestamp() > rhs->getToHandleTimestamp());
	};
};

class EventManager
{
public:
	static EventManager* getInstance();

	static bool scriptInitialized;
	
	void init(Timeline* timeline) { _timeline = timeline; };
	

	void dispatchEvents();
	void raiseEvent(Event* e);
	
	void registerFor(EventHandler* handler, std::string type);
private:
	EventManager();

	static EventManager* _instance;
	
	std::priority_queue<Event*, std::vector<Event*>, EventCompare> _PQ;
	std::unordered_map<std::string, std::vector<EventHandler*>> _registrationMap;

	Timeline* _timeline;

	std::mutex _lock;
};

