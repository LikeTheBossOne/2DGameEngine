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

Player::Player(Game* game, sf::Texture* texture, sf::Vector2f location, sf::Vector2f size) : Entity(game, size)
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

Player::Player(Game* game, sf::Vector2f location, sf::Vector2f size) : Entity(game, size)
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
	// Calculate Velocity
	_velocityX = _groundPlat != nullptr ? _groundPlat->getCurrentVelocityX() : 0;
	if (_groundPlat != nullptr)
	{
		_velocityY = _groundPlat->getCurrentVelocityY();
	}
	_velocityY += _accelerationY * deltaTime;


	// Get Inputs
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		_velocityX += -0.4; // Uses += to allow it to move normal speed relative to the platform it is on

		// Temporary solution to sprite change
		if (_orientation != Orientation::LEFT)
		{
			this->setTextureRect(sf::IntRect(0, 27, 17, 27));
			_orientation = Orientation::LEFT;
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		_velocityX += 0.4;

		// Temporary solution to sprite change
		if (_orientation != Orientation::RIGHT)
		{
			this->setTextureRect(sf::IntRect(0, 0, 17, 27));
			_orientation = Orientation::RIGHT;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && _groundPlat != nullptr)
	{
		_velocityY = -1.5;
		_groundPlat = nullptr;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		
	}

	const float prevX = this->getPosition().x;
	const float prevY = this->getPosition().y;
	
	this->move(_velocityX * deltaTime, _velocityY * deltaTime);

	bool grounded = false;
	// Check Collisions
	for (Entity* e : _game->getEntities())
	{
		// Check if platform type
		if (const auto plat = dynamic_cast<StaticPlatform*>(e))
		{
			sf::FloatRect rect;
			if (plat->getGlobalBounds().intersects(this->getGlobalBounds(), rect))
			{
				const float currentX = this->getPosition().x;
				const float currentY = this->getPosition().y;
				const float sizeX = this->getSize().x;
				const float sizeY = this->getSize().y;
				const float platX = plat->getPosition().x;
				const float platY = plat->getPosition().y;
				const float platSizeX = plat->getSize().x;
				const float platSizeY = plat->getSize().y;
				
				if (prevY + sizeY <= platY && currentY + sizeY > platY) // Can't go down
				{
					this->setPosition(currentX, platY - sizeY);
					_velocityY = 0;
					
					_groundPlat = plat;
					grounded = true;
				}
				if (prevY >= platY + platSizeY && currentY < platY + platSizeY) // Can't go up
				{
					this->setPosition(currentX, platY + platSizeY);
					_velocityY = 0;
				}
				if (prevX + sizeX <= platX && currentX + sizeX > platX) // Can't go right
				{
					this->setPosition(platX - sizeX, currentY);
					_velocityX = 0;
				}
				if (prevX >= platX + platSizeX && currentX < platX + platSizeX) // Can't go left
				{
					this->setPosition(platX + platSizeX, currentY);
					_velocityX = 0;
				}
			}
		}
		
		// Check if platform type
		if (const auto plat = dynamic_cast<PatternPlatform*>(e))
		{
			sf::FloatRect rect;
			if (plat->getGlobalBounds().intersects(this->getGlobalBounds(), rect))
			{
				const float currentX = this->getPosition().x;
				const float currentY = this->getPosition().y;
				const float sizeX = this->getSize().x;
				const float sizeY = this->getSize().y;
				const float prevPlatX = plat->getPrevX();
				const float prevPlatY = plat->getPrevY();
				const float platX = plat->getPosition().x;
				const float platY = plat->getPosition().y;
				const float platSizeX = plat->getSize().x;
				const float platSizeY = plat->getSize().y;

				if (prevY + sizeY <= prevPlatY && currentY + sizeY > platY) // Can't go down
				{
					this->setPosition(currentX, platY - sizeY);
					_velocityY = 0;

					_groundPlat = plat;
					grounded = true;
				}
				if (prevY >= prevPlatY + platSizeY && currentY < platY + platSizeY) // Can't go up
				{
					this->setPosition(currentX, platY + platSizeY);
					_velocityY = 0;
				}
				if (prevX + sizeX <= prevPlatX && currentX + sizeX > platX) // Can't go right
				{
					this->setPosition(platX - sizeX, currentY);
					_velocityX = 0;
				}
				if (prevX >= prevPlatX + platSizeX && currentX < platX + platSizeX) // Can't go left
				{
					this->setPosition(platX + platSizeX, currentY);
					_velocityX = 0;
				}
			}
		}
	}
	if (!grounded)
	{
		_groundPlat = nullptr;
	}
}

