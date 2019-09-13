#include "Game.h"
#include "PatternPlatform.h"
#include "Settings.h"
#include <iostream>
#include "Player.h"
#include "StaticPlatform.h"
#include <SFML/Graphics.hpp>
#include "Pattern.h"
#include "Entity.h"

Game::Game()
{
	_entities = std::vector<Entity*>();
}

void Game::run()
{
	// Create Window
	sf::ContextSettings settings;
	settings.antialiasingLevel = 4;
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Homework 1", sf::Style::Default, settings);
	window.setFramerateLimit(FRAMERATE);

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
	patterns.emplace_back(PatternTypes::RIGHT, 60, 1);
	patterns.emplace_back(PatternTypes::LEFT, 60, 1);
	patterns.emplace_back(PatternTypes::DOWN, 60, 2);
	patterns.emplace_back(PatternTypes::UP, 60, 2);
	PatternPlatform pPlat(this, sf::Vector2f(300, 200), sf::Vector2f(100.f, 40.f), patterns);

	_entities.emplace_back(&player);
	_entities.emplace_back(&floor);
	_entities.emplace_back(&sPlat);
	_entities.emplace_back(&pole);
	_entities.emplace_back(&pPlat);
	
	
	// Game Loop
	bool scaleMode = false;
	sf::View normalView = sf::View(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));
	window.setView(normalView);
	sf::View scaledView = normalView;
	int scaleChangeTime = 0;
	sf::Clock clock;
	while (window.isOpen())
	{
		scaleChangeTime++;
		
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			else if (event.type == sf::Event::Resized)
			{
				normalView = sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height));
				if (!scaleMode)
				{
					window.setView(normalView);
				}
			}
		}

		// Handle Scaling Input
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::V) && scaleChangeTime > 10)
		{
			scaleMode = !scaleMode;
			scaleChangeTime = 0;
			
			if (scaleMode) window.setView(scaledView);
			else window.setView(normalView);
		}
		

		// Tick
		sf::Time elapsed = clock.restart();
		pPlat.tick(elapsed);
		player.tick(elapsed);

		// Draw
		window.clear();
		window.draw(floor);
		window.draw(sPlat);
		window.draw(pole);
		window.draw(pPlat);
		window.draw(player);

		window.display();
	}
}
