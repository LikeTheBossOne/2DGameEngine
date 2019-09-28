#include "GameTime.h"
#include <cmath>

GameTime::GameTime(int stepSize)
{
	_stepSize = stepSize;
	
	_startTime = std::chrono::system_clock::now();
	_totalPausedDuration = std::chrono::milliseconds(0);
	_elapsed = 0;
	_prevGameTime = std::chrono::system_clock::now();
	
	_paused = false;
	_scale = 1.0;
}

GameTime::GameTime(GameTime& anchor, int stepSize)
{
	_stepSize = stepSize;
	
	_startTime = std::chrono::system_clock::now();
	_totalPausedDuration = std::chrono::milliseconds(0);
	_elapsed = 0;
	_prevGameTime = std::chrono::system_clock::now();
	
	_paused = false;
	_scale = 1.0;
}

bool GameTime::pause()
{
	if (_paused)
	{
		return false;
	}
	_pausedAt = std::chrono::system_clock::now();
	_paused = true;
	return true;
}

bool GameTime::resume()
{
	if (!_paused)
	{
		return false;
	}
	_totalPausedDuration += std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - _pausedAt);
	_paused = false;
	return true;
}

int GameTime::getTime()
{
	std::chrono::milliseconds elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - _startTime);
	return std::floor((elapsed - _totalPausedDuration).count() / (_stepSize * _scale));
}
