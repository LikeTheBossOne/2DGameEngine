#include "Game.h"
#include "Settings.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include "GameTime.h"
#include "EntityManager.h"
#include "ResourceManager.h"
#include <thread>
#include <zmq.hpp>

Game::Game(int clientNumber, int playerNumber)
{
	_shouldStartYet = false;
	_shouldEnd = false;

	_clientNumber = clientNumber;
	_playerNumber = playerNumber;
	
	_entityManager = new EntityManager(this);
	_resourceManager = new ResourceManager(this);

	// Load Textures
	auto lanceTexture = new sf::Texture();
	if (!lanceTexture->loadFromFile("assets/images/lance.png"))
	{
		std::cout << "Failed to load player texture" << std::endl;
		exit(EXIT_FAILURE);
	}
	auto poleTexture = new sf::Texture();
	if (!poleTexture->loadFromFile("assets/images/pole.png"))
	{
		std::cout << "Failed to load pole texture" << std::endl;
		exit(EXIT_FAILURE);
	}

	getResourceManager()->addTexture("lance", lanceTexture);
	getResourceManager()->addTexture("pole", poleTexture);

	// Lance animations
	auto lanceAnims = std::vector<sf::IntRect>();
	lanceAnims.emplace_back(0, 0, 17, 27);
	lanceAnims.emplace_back(0, 28, 17, 27);
	getResourceManager()->addTextureAnimations("lance", lanceAnims);
}

Game::~Game() = default;

void Game::run(zmq::socket_t& socket, std::mutex& myPlayerLock, std::mutex& playersLock, std::mutex& entitiesLock)
{
	// Create Window
	sf::ContextSettings settings;
	settings.antialiasingLevel = 4;
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Homework 1", sf::Style::Default, settings);

	
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
			else if (event.type == sf::Event::LostFocus) {
				gameTime.pause();
			}
			else if (event.type == sf::Event::GainedFocus) {
				gameTime.resume();
			}
		}

		// Handle Timeline setScale
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Dash)
			&& timeline.getScale() < 2
			&& timelineScaleChangeTime > 10
			&& !gameTime.getPaused())
		{
			timeline.setScale(timeline.getScale() * 2);
			previousTime /= 2;
			timelineScaleChangeTime = 0;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Equal)
			&& timeline.getScale() > 0.5
			&& timelineScaleChangeTime > 10
			&& !gameTime.getPaused())
		{
			timeline.setScale(timeline.getScale() / 2);
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
		// Decide whether to draw or wait
		deltaTime = timeline.getTime() - previousTime;
		int governor = std::floor(1000 / (FRAMERATE * STEP_SIZE));
		while (deltaTime < governor) // 8 is for ~ 1000 / (60 * 2)
		{
			// std::this_thread::sleep_for(std::chrono::milliseconds(governor - deltaTime));
			deltaTime = timeline.getTime() - previousTime;
		}
		previousTime = timeline.getTime();
		std::cout << 1000 / (deltaTime * STEP_SIZE * timeline.getScale()) << std::endl;


		// Send input
		std::string inputString = std::to_string(_playerNumber) + "\n";
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !gameTime.getPaused())
		{
			inputString.append("true");
		}
		else
		{
			inputString.append("false");
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !gameTime.getPaused())
		{
			inputString.append(",true");
		}
		else
		{
			inputString.append(",false");
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !gameTime.getPaused())
		{
			inputString.append(",true");
		}
		else
		{
			inputString.append(",false");
		}
		
		zmq::message_t inputMessage(inputString.data(), inputString.size());

		socket.send(inputMessage, zmq::send_flags::none);

		zmq::message_t response;
		socket.recv(response);
		auto responseString = std::string(static_cast<char*>(response.data()), response.size());

		// Update & Draw
		if (_shouldStartYet)
		{
			_entityManager->update(myPlayerLock);
			window.clear();
			_entityManager->draw(window, myPlayerLock, playersLock, entitiesLock);
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
	_shouldEnd = true;
	std::string inputString = std::to_string(this->getPlayerNumber()) + "\nCLOSE";
	zmq::message_t inputMessage(inputString.data(), inputString.size());

	socket.send(inputMessage, zmq::send_flags::none);

	zmq::message_t response;
	socket.recv(response);
	auto responseString = std::string(static_cast<char*>(response.data()), response.size());
	std::cout << responseString << std::endl;
	socket.close();
}
