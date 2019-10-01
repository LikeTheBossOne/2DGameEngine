#include "Player.h"
#include "Platform.h"
#include "Game.h"
#include <iostream>
#include "StaticPlatform.h"
#include "DynamicPlatform.h"
#include "PatternPlatform.h"
#include "InputManager.h"
#include "Inputs.h"
#include "Settings.h"
#include <algorithm>

Player::Player(Game* game, std::string textureName, float x, float y, float width, float height) : Entity(game, textureName, x, y, width, height)
{
	// this->setTextureRect(sf::IntRect(0, 0, 17, 27));
	
	_orientation = Orientation::RIGHT;

	_velocityX = 0;
	_velocityY = 0;
	_accelerationX = 0;
	_accelerationY = 0.01;
	_groundPlat = nullptr;
}

Player::Player(Game* game, float x, float y, float width, float height) : Entity(game, x, y, width, height)
{

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
	if (_game->getInputManager()->getPlayerKeysPressed(this->getGUID())[int(Inputs::LEFT)])
	{
		_velocityX += -0.4; // Uses += to allow it to move normal speed relative to the platform it is on

		// Temporary solution to sprite change
		if (_orientation != Orientation::LEFT)
		{
			// this->setTextureRect(sf::IntRect(0, 27, 17, 27));
			_orientation = Orientation::LEFT;
		}
	}
	else if (_game->getInputManager()->getPlayerKeysPressed(this->getGUID())[int(Inputs::RIGHT)])
	{
		_velocityX += 0.4;

		// Temporary solution to sprite change
		if (_orientation != Orientation::RIGHT)
		{
			// this->setTextureRect(sf::IntRect(0, 0, 17, 27));
			_orientation = Orientation::RIGHT;
		}
	}
	if (_game->getInputManager()->getPlayerKeysPressed(this->getGUID())[int(Inputs::UP)] && _groundPlat != nullptr)
	{
		_velocityY = -1.5;
		_groundPlat = nullptr;
	}

	const float prevX = this->getX();
	const float prevY = this->getY();
	
	this->move(_velocityX * deltaTime, _velocityY * deltaTime);

	bool grounded = false;
	// Check Collisions
	for (const std::pair<int, Entity*> ePairs : _game->getEntities())
	{
		// Check if platform type
		Entity* e = ePairs.second;
		if (const auto plat = dynamic_cast<StaticPlatform*>(e))
		{
			EntityRectangle rect;
			if (this->intersects(*plat, rect))
			{
				const float currentX = this->getX();
				const float currentY = this->getY();
				const float sizeX = this->getWidth();
				const float sizeY = this->getHeight();
				const float platX = plat->getX();
				const float platY = plat->getY();
				const float platSizeX = plat->getWidth();
				const float platSizeY = plat->getHeight();
				
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
					std::cout << "UP" << std::endl;
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
			EntityRectangle rect;
			if (this->intersects(*plat, rect))
			{
				const float currentX = this->getX();
				const float currentY = this->getY();
				const float sizeX = this->getWidth();
				const float sizeY = this->getHeight();
				const float prevPlatX = plat->getPrevX();
				const float prevPlatY = plat->getPrevY();
				const float platX = plat->getX();
				const float platY = plat->getY();
				const float platSizeX = plat->getWidth();
				const float platSizeY = plat->getHeight();

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
					_velocityY = std::max(_velocityY, 0.f);
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

	// Check if off screen
	if (this->getX() < 0)
	{
		this->setPosition(0, this->getY());
	}
	else if (this->getX() + this->getWidth() > WINDOW_WIDTH)
	{
		this->setPosition(WINDOW_WIDTH - this->getWidth(), this->getY());
	}
	if (this->getY() < 0)
	{
		// Stop velocity from continuing upwards
		this->setPosition(this->getY(), 0);
		_velocityY = 0; 
	}
	else if (this->getY() + this->getHeight() > WINDOW_HEIGHT)
	{
		this->setPosition(this->getX(), WINDOW_HEIGHT - this->getHeight());
	}
}

