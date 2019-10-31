#pragma once
#include <vector>
#include "Pattern.h"
#include "GenericComponent.h"

class PatternComponent : public GenericComponent
{
public:
	PatternComponent(GameObject* gameObject, std::vector<Pattern*> patterns);

	void update(int deltaTime) override;
	ComponentTypes getType() override { return ComponentTypes::PatternComponent; };

	void setPatterns(std::vector<Pattern*> patterns) { _patterns = patterns; }
	void setCurrentPattern(int currentPattern) { _currentPattern = currentPattern; }
	void setPatternGametimeCount(int patternGametimeCount) { _patternGametimeCount = patternGametimeCount; }
	
	std::vector<Pattern*> getPattern() { return _patterns; }
	int getCurrentPattern() { return _currentPattern; }
	int getPatternGametimeCount() { return _patternGametimeCount; }
private:
	float getCurrentVelocityX();
	float getCurrentVelocityY();
	
	std::vector<Pattern*> _patterns;

	int _currentPattern;
	int _patternGametimeCount;
	float _startOfPatternX;
	float _startOfPatternY;
};

