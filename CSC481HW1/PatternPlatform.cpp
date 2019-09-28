#include "PatternPlatform.h"
#include "Pattern.h"
#include <iostream>

PatternPlatform::
PatternPlatform(Game* game, sf::Texture* texture, sf::Vector2f location, sf::Vector2f size, std::vector<Pattern>& patterns)
	: DynamicPlatform(game, texture, location, size)
{
	_patterns = patterns;
	_currentPattern = 0;
	_patternGametimeCount = 0;

	_startOfPatternX = location.x;
	_startOfPatternY = location.y;
}

PatternPlatform::PatternPlatform(Game* game, sf::Vector2f location, sf::Vector2f size, std::vector<Pattern>& patterns)
	: DynamicPlatform(game, location, size)
{
	_patterns = patterns;
	_currentPattern = 0;
	_patternGametimeCount = 0;

	_startOfPatternX = location.x;
	_startOfPatternY = location.y;
}

void PatternPlatform::tick(int deltaTime)
{
	// Assign previous position
	_prevX = this->getPosition().x;
	_prevY = this->getPosition().y;
	
	
	Pattern* pat = &_patterns[_currentPattern];

	int remainingDelta = deltaTime;
	// Check if pattern will be finished after this deltaTime
	while (_patternGametimeCount + remainingDelta >= pat->getGametimeToComplete())
	{
		switch (pat->getType())
		{
			case PatternTypes::LEFT:
				this->setPosition(_startOfPatternX - float(pat->getDistance()), this->getPosition().y);
				break;
			case PatternTypes::RIGHT:
				this->setPosition(_startOfPatternX + float(pat->getDistance()), this->getPosition().y);
				break;
			case PatternTypes::UP:
				this->setPosition(this->getPosition().x, _startOfPatternY - float(pat->getDistance()));
				break;
			case PatternTypes::DOWN:
				this->setPosition(this->getPosition().x, _startOfPatternY + float(pat->getDistance()));
				break;
			default: break;
		}
		remainingDelta -= (pat->getGametimeToComplete() - _patternGametimeCount);
		
		if (_currentPattern >= _patterns.size() - 1)
		{
			_currentPattern = 0;
		}
		else
		{
			_currentPattern++;
		}
		pat = &_patterns[_currentPattern];
		_patternGametimeCount = 0;
		_startOfPatternX = this->getPosition().x;
		_startOfPatternY = this->getPosition().y;
	}
	switch (pat->getType())
	{
		case PatternTypes::LEFT:
			this->move(getCurrentVelocityX() * remainingDelta, 0);
			break;
		case PatternTypes::RIGHT:
			this->move(getCurrentVelocityX() * remainingDelta, 0);
			break;
		case PatternTypes::UP:
			this->move(0, getCurrentVelocityY() * remainingDelta);
			break;
		case PatternTypes::DOWN:
			this->move(0, getCurrentVelocityY() * remainingDelta);
			break;
		default: break;
	}
	_patternGametimeCount += remainingDelta;
}

Pattern PatternPlatform::getCurrentPattern()
{
	return _patterns[_currentPattern];
}

float PatternPlatform::getCurrentVelocityX()
{
	Pattern pat = getCurrentPattern();
	if (pat.getType() == PatternTypes::LEFT)
	{
		return -(pat.getDistance() / float(pat.getGametimeToComplete()));
	}
	else if (pat.getType() == PatternTypes::RIGHT)
	{
		return pat.getDistance() / float(pat.getGametimeToComplete());
	}
	return 0;
}

float PatternPlatform::getCurrentVelocityY()
{
	Pattern pat = getCurrentPattern();
	if (pat.getType() == PatternTypes::UP)
	{
		return -(pat.getDistance() / float(pat.getGametimeToComplete()));
	}
	else if (pat.getType() == PatternTypes::DOWN)
	{
		return pat.getDistance() / float(pat.getGametimeToComplete());
	}
	return 0;
}

PatternTypes PatternPlatform::getCurrentPatternType()
{
	return getCurrentPattern().getType();
}
