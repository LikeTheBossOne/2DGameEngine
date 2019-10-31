#include "Game.h"
#include "PatternPlatform.h"
#include "Settings.h"
#include "StaticPlatform.h"
#include "Pattern.h"
#include "EntityManager.h"
#include <thread>
#include "GameTime.h"
#include "Player.h"
#include "TransformComponent.h"
#include "TextureComponent.h"
#include "ColorComponent.h"
#include "SpawnZone.h"
#include <zmq.hpp>
#include "DeathZone.h"
#include "SideBoundaryComponent.h"
#include "SideBoundary.h"

Game::Game()
{
	_entityManager = new EntityManager(this);

	_totalPlayerCount = 0;
}

Game::~Game() = default;

void Game::run(zmq::socket_t& publisher)
{
	// Create Spawns
	auto firstSpawn = new SpawnZone(_entityManager->getPhysicsEngineSettings(), 20, 400);
	_entityManager->addSpawn(firstSpawn);
	
	// Create Platforms
	auto floor1 = new StaticPlatform(_entityManager->getPhysicsEngineSettings(),
	                                           Rect(0, WINDOW_HEIGHT - 100, WINDOW_WIDTH / 2 - 50, 100), 150, 50, 250);
	auto floor2 = new StaticPlatform(_entityManager->getPhysicsEngineSettings(),
											   Rect(WINDOW_WIDTH / 2 + 50, WINDOW_HEIGHT - 100, WINDOW_WIDTH - 50, 100), 150, 50, 250);
	auto death1 = new DeathZone(_entityManager->getPhysicsEngineSettings(), Rect(-1000, WINDOW_HEIGHT - 60, 4000, 60));
	auto sPlatRed = new StaticPlatform(_entityManager->getPhysicsEngineSettings(),
	                                              Rect(100, 390, 100.f, 40.f), 255, 10, 10);
	auto sPlatBlue = new StaticPlatform(_entityManager->getPhysicsEngineSettings(),
	                                               Rect(500, 390, 100.f, 40.f), 10, 10, 255);
	// StaticPlatform pole(this, "pole", 740, 100, 60.f, 400.f);
	// pole.setTextureRect(new EngineRectangle(0, 0, 27, 168));

	std::vector<Pattern*> patterns;
	patterns.emplace_back(new Pattern(PatternTypes::RIGHT, 1000, 100));
	patterns.emplace_back(new Pattern(PatternTypes::LEFT, 1000, 100));
	patterns.emplace_back(new Pattern(PatternTypes::DOWN, 1000, 150));
	patterns.emplace_back(new Pattern(PatternTypes::UP, 1000, 150));
	auto pPlat1 = new PatternPlatform(_entityManager->getPhysicsEngineSettings(),
						 Rect(300, 200, 100.f, 40.f), 150, 50, 250, patterns);

	std::vector<Pattern*> patterns2;
	patterns2.emplace_back(new Pattern(PatternTypes::RIGHT, 1000, 200));
	patterns2.emplace_back(new Pattern(PatternTypes::LEFT, 1000, 200));
	auto pPlat2 = new PatternPlatform(_entityManager->getPhysicsEngineSettings(),
		Rect(3 * WINDOW_WIDTH / 2, 400, 100.f, 40.f), 10, 255, 10, patterns2);

	auto sideBoundary = new SideBoundary(_entityManager->getPhysicsEngineSettings(), WINDOW_WIDTH, WINDOW_WIDTH);

	_entityManager->addEntity(firstSpawn);
	_entityManager->addEntity(floor1);
	_entityManager->addEntity(floor2);
	_entityManager->addEntity(death1);
	_entityManager->addEntity(sPlatRed);
	_entityManager->addEntity(sPlatBlue);
	// _entityManager->addEntity(&pole);
	_entityManager->addEntity(pPlat1);
	_entityManager->addEntity(pPlat2);
	_entityManager->addEntity(sideBoundary);

	int STEP_SIZE = 2;
	GameTime gameTime(STEP_SIZE);
	int previousTime = gameTime.getTime();
	int deltaTime = 0;
	
	bool running = true;
	while (running)
	{
		// Decide whether to update or wait
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
		_entityManager->update(deltaTime);


		// Display
		std::map<int, GameObject*> entities = _entityManager->getEntities();

		
		// Publish to client
		std::string entitiesString;
		for (std::pair<int, GameObject*> pPair : entities)
		{
			auto entity = pPair.second;

			if (entity->getType() == "SpawnZone" || entity->getType() == "DeathZone") continue;
			
			entitiesString += std::to_string(entity->getGUID()) + ",";
			
			entitiesString += entity->getType() + ",";

			if (entity->getType() == "SideBoundary")
			{
				entitiesString += std::to_string(entity->getTransform()->getPositionX()) + ",";
				entitiesString += std::to_string(dynamic_cast<SideBoundaryComponent*>(entity->getComponent(
					ComponentTypes::SideBoundaryComponent))->getSceneShiftWidth());
			}
			else
			{
				entitiesString += std::to_string(entity->getTransform()->getPositionX()) + ",";
				entitiesString += std::to_string(entity->getTransform()->getPositionY()) + ",";
				entitiesString += std::to_string(entity->getTransform()->getWidth()) + ",";
				entitiesString += std::to_string(entity->getTransform()->getHeight()) + ",";

				const auto gTexture = entity->getComponent(ComponentTypes::TextureComponent);
				const auto gColor = entity->getComponent(ComponentTypes::ColorComponent);
				if (gTexture != nullptr)
				{
					auto texture = dynamic_cast<TextureComponent*>(gTexture);
					entitiesString.append("Texture,");
					entitiesString += texture->getTextureName() + ",";
					entitiesString.append(std::to_string(texture->getAnimationNumber()));
				}
				else if (gColor != nullptr)
				{
					auto color = dynamic_cast<ColorComponent*>(gColor);
					entitiesString.append("Color,");
					entitiesString += std::to_string(color->getR()) + ",";
					entitiesString += std::to_string(color->getG()) + ",";
					entitiesString += std::to_string(color->getB());
				}
				else
				{
					entitiesString.append("None");
				}
			}

			entitiesString += "\n";
		}
		
		zmq::message_t entitiesMessage(entitiesString.data(), entitiesString.size());
		publisher.send(entitiesMessage, zmq::send_flags::none);
	}
}

