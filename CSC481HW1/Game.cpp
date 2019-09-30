#include "Game.h"
#include "Settings.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "GameTime.h"
#include "EntityManager.h"
#include <thread>
#include <zmq.hpp>

Game::Game(int playerNumber)
{
	_shouldStartYet = false;
	
	_playerNumber = playerNumber;
	
	_entityManager = new EntityManager();

	_texturesMap = std::map<std::string, sf::Texture>();

	// Load Textures
	sf::Texture lanceTexture;
	if (!lanceTexture.loadFromFile("assets/images/lance.png"))
	{
		std::cout << "Failed to load player texture" << std::endl;
		exit(1);
	}
	sf::Texture poleTexture;
	if (!poleTexture.loadFromFile("assets/images/pole.png"))
	{
		std::cout << "Failed to load pole texture" << std::endl;
		exit(1);
	}

	setTexture("lance", lanceTexture);
	setTexture("pole", poleTexture);
}

void Game::setTexture(std::string name, sf::Texture texture)
{
	_texturesMap[name] = texture;
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
			// _entityManager->tick(deltaTime);


			// Send input
			std::string inputString = std::to_string(_playerNumber) + "\n";
			
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{
				inputString.append("true");
			}
			else
			{
				inputString.append("false");
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			{
				inputString.append(",true");
			}
			else
			{
				inputString.append(",false");
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
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
			std::cout << responseString << std::endl;
		}


		// Draw
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
