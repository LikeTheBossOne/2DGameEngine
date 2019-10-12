#pragma once
#include <chrono>
#include "Timeline.h"

class GameTime : public Timeline
{
public:
	GameTime(int stepSize);
	GameTime(GameTime& anchor, int stepSize);
	
	bool pause();
	bool resume();

	int getTime() override;

	float getScale() { return _scale; }
	void setScale(float scale) { _scale = scale; }

	bool getPaused() { return _paused; }
private:
	std::chrono::system_clock::time_point _startTime;
	std::chrono::milliseconds _totalPausedDuration{};
	int _elapsed;
	std::chrono::system_clock::time_point _prevGameTime;

	std::chrono::system_clock::time_point _pausedAt;

	int _stepSize;
	
	bool _paused;
	
	float _scale;
};

