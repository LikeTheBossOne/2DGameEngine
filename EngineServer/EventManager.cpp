#include "EventManager.h"
#include "EventHandler.h"
#include "Timeline.h"
#include "ScriptManager.h"
#include "duktape.h"
#include "dukglue/dukglue.h"
#include "SpawnEvent.h"

EventManager* EventManager::_instance;

bool EventManager::scriptInitialized = false;

EventManager::EventManager()
{
	if (!scriptInitialized)
	{
		// duk_context* ctx = ScriptManager::getInstance()->getContext();
		// dukglue_register_method(ctx, &EventManager::raiseSEvent, "raiseSEvent");
		
		scriptInitialized = true;
	}
	_PQ = std::priority_queue<Event*, std::vector<Event*>, EventCompare>();
	_registrationMap = std::unordered_map<std::string, std::vector<EventHandler*>>();

	_timeline = nullptr;
};

EventManager* EventManager::getInstance()
{
	if (_instance == nullptr)
	{
		_instance = new EventManager();
	}
	return _instance;
}

/**
 * Make sure we deallocate the event after it has been handled
 */
void EventManager::dispatchEvents()
{
	if (_PQ.empty()) return;

	std::unique_lock<std::mutex> uniqueLock(_lock);

	// Loop through events
	auto e = _PQ.top();
	while (e != nullptr && e->getToHandleTimestamp() <= _timeline->getTime())
	{
		_PQ.pop();
		uniqueLock.unlock();

		if (_registrationMap.find(e->getType()) != _registrationMap.end())
		{
			auto handlers = _registrationMap[e->getType()];

			for (auto handler : handlers)
			{
				handler->onEvent(e);
			}
		}
		
		// HAKAI
		delete e;

		if (_PQ.empty())
		{
			e = nullptr;
		}
		else
		{
			uniqueLock.lock();
			e = _PQ.top();
		}
	}
}

void EventManager::raiseEvent(Event* e)
{
	_lock.lock();
	e->setTimestamp(_timeline->getTime());
	e->createHandleTime(_timeline->getTime());
	_PQ.push(e);
	_lock.unlock();
}

void EventManager::registerFor(EventHandler* handler, std::string type)
{
	if (_registrationMap.count(type))
	{
		_registrationMap[type].emplace_back(handler);
	}
	else
	{
		auto handlers = std::vector<EventHandler*>();
		handlers.emplace_back(handler);
		_registrationMap[type] = handlers;
	}
	
}
