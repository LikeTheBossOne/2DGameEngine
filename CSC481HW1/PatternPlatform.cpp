#include "PatternPlatform.h"
#include "Pattern.h"
#include <iostream>

PatternPlatform::
PatternPlatform(Game* game, sf::Texture* texture, sf::Vector2f location, sf::Vector2f size, std::vector<Pattern>& patterns)
	: DynamicPlatform(game, texture, location, size)
{
	_patterns = patterns;
	_currentPattern = 0;
	_patternTickCount = -1;
}

PatternPlatform::PatternPlatform(Game* game, sf::Vector2f location, sf::Vector2f size, std::vector<Pattern>& patterns)
	: DynamicPlatform(game, location, size)
{
	_patterns = patterns;
	_currentPattern = 0;
	_patternTickCount = -1;
}

void PatternPlatform::tick(sf::Time deltaTime)
{
	// Calculate current state
	Pattern* pat = &_patterns[_currentPattern];
	_patternTickCount++;
	
	if (_patternTickCount >= pat->getTicksToComplete())
	{
		_patternTickCount = 0;
		
		if (_currentPattern >= _patterns.size() - 1)
		{
			_currentPattern = 0;
		} else
		{
			_currentPattern++;
		}
	}
	pat = &_patterns[_currentPattern];

	// Record Previous location;
	_prevX = this->getPosition().x;
	_prevY = this->getPosition().y;

	// Change Location;
	float distance = pat->getVelocity();
	switch (pat->getType())
	{
		case PatternTypes::LEFT:
			this->move(-distance, 0);
			break;
		case PatternTypes::RIGHT:
			this->move(distance, 0);
			break;
		case PatternTypes::UP:
			this->move(0, -distance);
			break;
		case PatternTypes::DOWN:
			this->move(0, distance);
			break;
		default: break;
	}

	// printf("X:%f, Y:%f\n", this->getPosition().x, this->getPosition().y);
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
		return -pat.getVelocity();
	}
	else if (pat.getType() == PatternTypes::RIGHT)
	{
		return pat.getVelocity();
	}
	return 0;
}

float PatternPlatform::getCurrentVelocityY()
{
	Pattern pat = getCurrentPattern();
	if (pat.getType() == PatternTypes::UP)
	{
		return -pat.getVelocity();
	}
	else if (pat.getType() == PatternTypes::DOWN)
	{
		return pat.getVelocity();
	}
	return 0;
}

PatternTypes PatternPlatform::getCurrentPatternType()
{
	return getCurrentPattern().getType();
}
