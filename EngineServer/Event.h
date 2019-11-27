#pragma once
#include <string>

class Event
{
public:
	Event(int priority, int timeTillHandle);
	Event(const Event& obj) = default;
	virtual ~Event() = default;

	void setTimestamp(int timestamp) { _timestamp = timestamp; }
	void createHandleTime(int timestamp) { _toHandleTimestamp = timestamp + _timeTillHandle; }
	
	virtual std::string getType() = 0;
	int getPriority() { return _priority; }
	int getTimestamp() { return _timestamp; }
	int getToHandleTimestamp() { return _toHandleTimestamp; }

protected:
	int _priority;
	int _timestamp;

	int _timeTillHandle;
	int _toHandleTimestamp;
};

