#include "PatternComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"

PatternComponent::PatternComponent(GameObject* gameObject, std::vector<Pattern*> patterns) : GenericComponent(gameObject)
{
	_patterns = patterns;
	_currentPattern = 0;
	_patternGametimeCount = 0;

	_startOfPatternX = _gameObject->getTransform()->getPositionX();
	_startOfPatternY = _gameObject->getTransform()->getPositionY();
}

PatternComponent::PatternComponent(const PatternComponent& other, GameObject* gameObject) : GenericComponent(gameObject)
{
	_patterns = other._patterns;
	_currentPattern = other._currentPattern;
	_patternGametimeCount = other._patternGametimeCount;
	_startOfPatternX = other._startOfPatternX;
	_startOfPatternY = other._startOfPatternY;
}

void PatternComponent::update(int deltaTime)
{
	auto transform = _gameObject->getTransform();

	
	int remainingDelta = deltaTime;

	Pattern** pat = &_patterns[_currentPattern];
	
	while (_patternGametimeCount + remainingDelta >= (*pat)->getGametimeToComplete())
	{
		switch ((*pat)->getType())
		{
		case PatternTypes::LEFT:
			transform->setPositionX(_startOfPatternX - float((*pat)->getDistance()));
			break;
		case PatternTypes::RIGHT:
			transform->setPositionX(_startOfPatternX + float((*pat)->getDistance()));
			break;
		case PatternTypes::UP:
			transform->setPositionY(_startOfPatternY - float((*pat)->getDistance()));
			break;
		case PatternTypes::DOWN:
			transform->setPositionY(_startOfPatternY + float((*pat)->getDistance()));
			break;
		default: break;
		}
		remainingDelta -= ((*pat)->getGametimeToComplete() - _patternGametimeCount);

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
		_startOfPatternX = transform->getPositionX();
		_startOfPatternY = transform->getPositionY();
	}

	switch ((*pat)->getType())
	{
	case PatternTypes::LEFT:
		transform->setPositionX(transform->getPositionX() + getCurrentVelocityX() * float(remainingDelta));
		break;
	case PatternTypes::RIGHT:
		transform->setPositionX(transform->getPositionX() + getCurrentVelocityX() * float(remainingDelta));
		break;
	case PatternTypes::UP:
		transform->setPositionY(transform->getPositionY() - getCurrentVelocityY() * float(remainingDelta));
		break;
	case PatternTypes::DOWN:
		transform->setPositionY(transform->getPositionY() - getCurrentVelocityY() * float(remainingDelta));
		break;
	default: break;
	}
	_patternGametimeCount += remainingDelta;
}

float PatternComponent::getCurrentVelocityX()
{
	Pattern* pat = _patterns[_currentPattern];
	if (pat->getType() == PatternTypes::LEFT)
	{
		return -(pat->getDistance() / float(pat->getGametimeToComplete()));
	}
	else if (pat->getType() == PatternTypes::RIGHT)
	{
		return pat->getDistance() / float(pat->getGametimeToComplete());
	}
	return 0;
}

float PatternComponent::getCurrentVelocityY()
{
	Pattern* pat = _patterns[_currentPattern];
	if (pat->getType() == PatternTypes::UP)
	{
		return pat->getDistance() / float(pat->getGametimeToComplete());
	}
	else if (pat->getType() == PatternTypes::DOWN)
	{
		return -(pat->getDistance() / float(pat->getGametimeToComplete()));
	}
	return 0;
}
