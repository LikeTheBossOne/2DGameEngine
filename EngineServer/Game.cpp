#include "Game.h"
#include "PatternPlatform.h"
#include "Settings.h"
#include <iostream>
#include "StaticPlatform.h"
#include "Pattern.h"
#include "Entity.h"
#include "EntityManager.h"
#include "InputManager.h"
#include <thread>
#include "GameTime.h"
#include "Player.h"
#include <zmq.hpp>

Game::Game()
{
	_entityManager = new EntityManager(this);
	_inputManager = new InputManager(this);
}

Game::~Game() = default;

void Game::run(zmq::socket_t& publisher)
{
	// Create Platforms
	StaticPlatform floor(this, 0, WINDOW_HEIGHT - 100, WINDOW_WIDTH, 100);
	StaticPlatform sPlat(this, 100, 396, 100.f, 40.f);
	StaticPlatform pole(this, "pole", 740, 100, 60.f, 400.f);
	pole.setTextureRect(new EntityRectangle(0, 0, 27, 168));

	std::vector<Pattern> patterns;
	patterns.emplace_back(PatternTypes::RIGHT, 1000, 100);
	patterns.emplace_back(PatternTypes::LEFT, 1000, 100);
	patterns.emplace_back(PatternTypes::DOWN, 1000, 150);
	patterns.emplace_back(PatternTypes::UP, 1000, 150);
	PatternPlatform pPlat(this, 300, 200, 100.f, 40.f, patterns);

	// _entityManager->setPlayer(&player);
	_entityManager->addEntity(&floor);
	_entityManager->addEntity(&sPlat);
	_entityManager->addEntity(&pole);
	_entityManager->addEntity(&pPlat);

	int STEP_SIZE = 2;
	GameTime gameTime(STEP_SIZE);
	int previousTime = gameTime.getTime();
	int deltaTime = 0;
	
	bool running = true;
	while (running)
	{
		// Decide whether to tick or wait
		deltaTime = gameTime.getTime() - previousTime;
		int governor = std::floor(1000 / (FRAMERATE * STEP_SIZE));
		while (deltaTime < governor) // 8 is for ~ 1000 / (60 * 2)
		{
			// std::this_thread::sleep_for(std::chrono::milliseconds(governor - deltaTime));
			deltaTime = gameTime.getTime() - previousTime;
		}
		deltaTime = gameTime.getTime() - previousTime;
		previousTime = gameTime.getTime();
		// std::cout << 1000 / (deltaTime * STEP_SIZE * gameTime.getScale()) << std::endl;
		// std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - prevRT).count() << std::endl;;

		// Tick
		_entityManager->tick(deltaTime);


		// Display
		std::map<int, Player*> players = _entityManager->getPlayers();
		std::map<int, Entity*> entities = _entityManager->getEntities();

		for (std::pair<int, Player*> pPair : players)
		{
			Player* p = pPair.second;
			// std::cout << p->getGUID() << "X: " << p->getX() << "Y: " << p->getY() << std::endl;
		}
		// for (std::pair<int, Entity*> ePair : entities)
		// {
		// 	Entity* e = ePair.second;
		// 	std::cout << e->getGUID() << "X: " << e->getX() << "Y: " << e->getY() << std::endl;
		// }


		
		// Publish to client
		std::string entitiesString;
		for (std::pair<int, Player*> pPair : players)
		{
			Player* p = pPair.second;
			entitiesString += std::to_string(p->getGUID()) + ",";
			entitiesString += "player,";
			entitiesString += std::to_string(p->getX()) + ",";
			entitiesString += std::to_string(p->getY()) + ",";
			entitiesString += std::to_string(p->getWidth()) + ",";
			entitiesString += std::to_string(p->getHeight()) + ",";
			EntityRectangle* r = p->getTextureRect();
			if (r == nullptr)
			{
				entitiesString.append("false");
			}
			else
			{
				entitiesString.append("true,");
				entitiesString += std::to_string(r->getX()) + ",";
				entitiesString += std::to_string(r->getY()) + ",";
				entitiesString += std::to_string(r->getWidth()) + ",";
				entitiesString += std::to_string(r->getHeight()) + ",";
				entitiesString += p->getTextureName();
			}

			entitiesString += "\n";
		}

		for (std::pair<int, Entity*> pPair : entities)
		{
			Entity* e = pPair.second;
			entitiesString += std::to_string(e->getGUID()) + ",";
			entitiesString += "entity,";
			entitiesString += std::to_string(e->getX()) + ",";
			entitiesString += std::to_string(e->getY()) + ",";
			entitiesString += std::to_string(e->getWidth()) + ",";
			entitiesString += std::to_string(e->getHeight()) + ",";
			EntityRectangle* r = e->getTextureRect();
			if (r == nullptr)
			{
				entitiesString.append("false");
			}
			else
			{
				entitiesString.append("true,");
				entitiesString += std::to_string(r->getX()) + ",";
				entitiesString += std::to_string(r->getY()) + ",";
				entitiesString += std::to_string(r->getWidth()) + ",";
				entitiesString += std::to_string(r->getHeight()) + ",";
				entitiesString += e->getTextureName();
			}

			entitiesString += "\n";
		}
		
		zmq::message_t entitiesMessage(entitiesString.data(), entitiesString.size());
		publisher.send(entitiesMessage, zmq::send_flags::none);
	}
}

std::map<int, Entity*> Game::getEntities()
{
	return _entityManager->getEntities();
}
