#include "Game.h"
#include "PatternPlatform.h"
#include "Settings.h"
#include <iostream>
#include "Player.h"
#include "StaticPlatform.h"
#include <SFML/Graphics.hpp>
#include "Pattern.h"
#include "Entity.h"
#include "GameTime.h"
#include "EntityManager.h"
#include <thread>

Game::Game()
{
	_entityManager = new EntityManager();
}

Game::~Game() = default;

void Game::run()
{
	// Create Window
	sf::ContextSettings settings;
	settings.antialiasingLevel = 4;
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Homework 1", sf::Style::Default, settings);
	// window.setFramerateLimit(FRAMERATE); // Remove this

	// Load Textures
	sf::Texture playerTexture;
	if (!playerTexture.loadFromFile("assets/images/lance.png"))
	{
		std::cout << "Failed to load player texture" << std::endl;
		return;
	}
	sf::Texture poleTexture;
	if (!poleTexture.loadFromFile("assets/images/pole.png"))
	{
		std::cout << "Failed to load pole texture" << std::endl;
		return;
	}

	// Create Player
	Player player(this, &playerTexture, sf::Vector2f(20, 400), sf::Vector2f(36, 64));

	// Create Platforms
	StaticPlatform floor(this, sf::Vector2f(0, WINDOW_HEIGHT - 100), sf::Vector2f(WINDOW_WIDTH, 100));
	StaticPlatform sPlat(this, sf::Vector2f(100, 396), sf::Vector2f(100.f, 40.f));
	StaticPlatform pole(this, &poleTexture, sf::Vector2f(740, 100), sf::Vector2f(60.f, 400.f));
	pole.setTextureRect(sf::IntRect(0, 0, 27, 168));

	std::vector<Pattern> patterns;
	patterns.emplace_back(PatternTypes::RIGHT, 1000, 100);
	patterns.emplace_back(PatternTypes::LEFT, 1000, 100);
	patterns.emplace_back(PatternTypes::DOWN, 1000, 150);
	patterns.emplace_back(PatternTypes::UP, 1000, 150);
	PatternPlatform pPlat(this, sf::Vector2f(300, 200), sf::Vector2f(100.f, 40.f), patterns);

	_entityManager->setPlayer(&player);
	_entityManager->addEntity(&floor);
	_entityManager->addEntity(&sPlat);
	_entityManager->addEntity(&pole);
	_entityManager->addEntity(&pPlat);

	// Timeline values
	int timelineScaleChangeTime = 0;

	// Start Real Timeline
	int STEP_SIZE = 2;
	GameTime timeline(STEP_SIZE);
	int pauseResumeTime = 0;

	// Start Game Timeline
	GameTime gameTime(STEP_SIZE);
	int previousTime = gameTime.getTime();
	int deltaTime = 0;
	// std::chrono::system_clock::time_point prevRT = std::chrono::system_clock::now();
	while (window.isOpen())
	{	
		timelineScaleChangeTime++;


		// HANDLE INPUT
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		// Handle Timeline setScale
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Dash)
			&& gameTime.getScale() < 2
			&& timelineScaleChangeTime > 10
			&& !gameTime.getPaused())
		{
			gameTime.setScale(gameTime.getScale() * 2);
			previousTime /= 2;
			timelineScaleChangeTime = 0;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Equal)
			&& gameTime.getScale() > 0.5
			&& timelineScaleChangeTime > 10
			&& !gameTime.getPaused())
		{
			gameTime.setScale(gameTime.getScale() / 2);
			previousTime *= 2;
			timelineScaleChangeTime = 0;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)
			&& timeline.getTime() - pauseResumeTime > 500)
		{
			pauseResumeTime = timeline.getTime();
			if (gameTime.getPaused())
			{
				gameTime.resume();
			}
			else
			{
				gameTime.pause();
			}
		}

		

		
		// In Game
		if (!gameTime.getPaused())
		{
			// Decide whether to draw or wait
			deltaTime = gameTime.getTime() - previousTime;
			int governor = std::floor(1000 / (FRAMERATE * STEP_SIZE));
			while (deltaTime < governor) // 8 is for ~ 1000 / (60 * 2)
			{
				// std::this_thread::sleep_for(std::chrono::milliseconds(governor - deltaTime));
				deltaTime = gameTime.getTime() - previousTime;
			}
			deltaTime = gameTime.getTime() - previousTime;
			previousTime = gameTime.getTime();
			std::cout << 1000 / (deltaTime * STEP_SIZE * gameTime.getScale()) << std::endl;
			// std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - prevRT).count() << std::endl;;
			// prevRT = std::chrono::system_clock::now();

			// Tick
			_entityManager->tick(deltaTime);
		}
		

		// Draw
		window.clear();
		_entityManager->draw(window);
		if (gameTime.getPaused())
		{
			sf::Text text;
			text.setPosition(0, 0);
			sf::Font font;
			font.loadFromFile("assets/fonts/OpenSans-Bold.ttf");
			text.setFont(font);
			text.setString("PAUSE");
			text.setCharacterSize(30);
			text.setFillColor(sf::Color::Red);
			text.setOutlineColor(sf::Color::Red);
			window.draw(text);
		}
		window.display();
	}
}

std::vector<Entity*> Game::getEntities()
{
	return _entityManager->getEntities();
}
