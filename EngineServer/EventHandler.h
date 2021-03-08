#pragma once
class Event;

class EventHandler
{
public:
	EventHandler();
	virtual ~EventHandler() = default;
	virtual void onEvent(Event* e) = 0;
};

