#pragma once
#include "DynamicPlatform.h"
#include "PatternTypes.h"
#include "SFML/System/Time.hpp"

class Pattern;

class PatternPlatform : public DynamicPlatform
{
public:
	PatternPlatform(Game* game, sf::Texture* texture, sf::Vector2f location, sf::Vector2f size, std::vector<Pattern>& patterns);

	PatternPlatform(Game* game, sf::Vector2f location, sf::Vector2f size, std::vector<Pattern>& patterns);
	void tick(sf::Time deltaTime) override;

	Pattern getCurrentPattern();
	float getCurrentVelocityX() override;
	float getCurrentVelocityY() override;
	PatternTypes getCurrentPatternType();
private:
	std::vector<Pattern> _patterns;
	int _currentPattern;
	int _patternTickCount;
};

