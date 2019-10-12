#include "Player.h"
#include <typeinfo>
#include "SFML/Graphics/Texture.hpp"
#include "SFML/System/Time.hpp"
#include <SFML/Window/Keyboard.hpp>
#include "Platform.h"
#include "Game.h"
#include <iostream>
#include "Platform.h"
#include "StaticPlatform.h"
#include "DynamicPlatform.h"
#include "PatternPlatform.h"

Player::Player(Game* game, int GUID, sf::Texture* texture, sf::Vector2f location, sf::Vector2f size) : Entity(game, GUID, size)
{
	this->setTexture(texture);
	
	// This is a temporary hardcode for Lance sprite
	this->setTextureRect(sf::IntRect(0, 0, 17, 27));
	_orientation = Orientation::RIGHT;
	
	this->setPosition(location);

	_velocityX = 0;
	_velocityY = 0;
	_accelerationX = 0;
	_accelerationY = 0.01;
	_groundPlat = nullptr;
}

Player::Player(Game* game, int GUID, sf::Vector2f location, sf::Vector2f size) : Entity(game, GUID, size)
{
	this->setFillColor(sf::Color(150, 50, 250));
	this->setPosition(location);

	_orientation = Orientation::RIGHT;
	
	_velocityX = 0;
	_velocityY = 0;
	_accelerationX = 0;
	_accelerationY = 0.01;
	_groundPlat = nullptr;
}

Player::~Player()
= default;

void Player::tick(int deltaTime)
{
	
}

