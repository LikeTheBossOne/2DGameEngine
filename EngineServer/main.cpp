#include <thread>
#include <zmq.hpp>
#include <iostream>
#include "Game.h"
#include "Player.h"
#include "EntityManager.h"
#include "InputManager.h"

const std::string REQREP_PORT = "tcp://*:5555";
const std::string PUBSUB_PORT = "tcp://*:5560";

void reqRepCommunication(Game& game, zmq::context_t& context)
{
	zmq::socket_t registrar(context, ZMQ_REP);
	registrar.bind(REQREP_PORT);

	while (true)
	{
		zmq::message_t request;
		registrar.recv(request);
		auto requestString = std::string(static_cast<char*>(request.data()), request.size());
		if (requestString == "OPEN")
		{
			// Create Player for client
			Player* clientsPlayer = new Player(game.getEntityManager()->getPhysicsEngineSettings(), Rect(20, 400, 36, 64), "lance");
			InputManager::getInstance()->setInputs(clientsPlayer->getGUID(), std::vector<bool>(3, false));
			game.getEntityManager()->addEntity(clientsPlayer);

			// Assign client id based on player _GUID
			auto responseString = std::to_string(clientsPlayer->getGUID()) + " " + std::to_string(game.getTotalPlayerCount());
			zmq::message_t response(responseString.data(), responseString.size());
			
			registrar.send(response, zmq::send_flags::none);
		}
		else
		{
			std::istringstream f(requestString);
			
			// Get player number
			std::string playerNumberString;
			std::getline(f, playerNumberString);
			
			int playerNumber = std::stoi(playerNumberString);
			
			// Get player input
			std::vector<bool> keys;
			
			std::string inputString;
			std::getline(f, inputString);

			// Remove player
			if (inputString == "CLOSE")
			{
				game.getEntityManager()->deleteEntity(playerNumber);
			}
			else
			{
				std::istringstream inputKeyStream(inputString);

				std::string key;
				while (std::getline(inputKeyStream, key, ','))
				{
					if (key == "true")
					{
						keys.emplace_back(true);
					}
					else if (key == "false")
					{
						keys.emplace_back(false);
					}

				}
				InputManager::getInstance()->setInputs(playerNumber, keys);
			}

			
			// Respond
			std::string responseString = "THANKS";
			zmq::message_t response(responseString.data(), responseString.size());
			registrar.send(response, zmq::send_flags::none);
		}
	}
}

int main()
{
	// Start Everything up
	Game game;

	// Create Thread for client -> server communication
	
	zmq::context_t context(1);
	std::thread reqReplyThread(
		reqRepCommunication, 
		std::ref(game),
		std::ref(context)
	);

	zmq::socket_t publisher(context, ZMQ_PUB);
	publisher.bind(PUBSUB_PORT);

	game.run(publisher);
}
