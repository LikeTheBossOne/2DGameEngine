#pragma once
#include "DynamicPlatform.h"
#include "PatternTypes.h"
#include <vector>

class Pattern;

class PatternPlatform : public DynamicPlatform
{
public:
	PatternPlatform(Game* game, std::string textureName, float x, float y, float width, float height, std::vector<Pattern>& patterns);

	PatternPlatform(Game* game, float x, float y, float width, float height, std::vector<Pattern>& patterns);
	void tick(int deltaTime) override;

	Pattern getCurrentPattern();
	float getCurrentVelocityX() override;
	float getCurrentVelocityY() override;
	PatternTypes getCurrentPatternType();
private:
	std::vector<Pattern> _patterns;
	int _currentPattern;
	int _patternGametimeCount;

	float _startOfPatternX;
	float _startOfPatternY;
};

