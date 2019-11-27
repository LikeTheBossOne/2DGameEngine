#include <thread>
#include <zmq.hpp>
#include <iostream>
#include "Game.h"
#include "Player.h"
#include "EntityManager.h"
#include "InputManager.h"
#include "InputEvent.h"
#include "EventManager.h"
#include "StartRecordingEvent.h"
#include "StopRecordingEvent.h"
#include "StartReplayEvent.h"
#include "ReplaySystem.h"
#include "Replay.h"
#include "ChangeReplaySpeedEvent.h"
#include "duktape.h"

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
			Player* clientsPlayer = new Player(game.getEntityManager()->getPhysicsEngineSettings(), 36, 64, "lance",
			                                   game.getEntityManager()->getSpawns()[0]);
			auto inputEvent = new InputEvent(clientsPlayer->getGUID(), std::bitset<3>(false));
			EventManager::getInstance()->raiseEvent(inputEvent);
			game.getEntityManager()->addEntity(clientsPlayer);

			// Assign client id based on player _GUID
			auto responseString = std::to_string(clientsPlayer->getGUID()) + " " + std::to_string(game.getTotalPlayerCount());
			zmq::message_t response(responseString.data(), responseString.size());
			
			registrar.send(response, zmq::send_flags::none);
		}
		else if (requestString == "START_RECORDING")
		{
			EventManager::getInstance()->raiseEvent(new StartRecordingEvent(
				new Replay(game.getEntityManager()->getEntities(), game.getEntityManager()->getPhysicsEngineSettings())));

			// Respond
			std::string responseString = "THANKS";
			zmq::message_t response(responseString.data(), responseString.size());
			registrar.send(response, zmq::send_flags::none);
		}
		else if (requestString == "STOP_RECORDING") // Stop recording and start replay
		{
			EventManager::getInstance()->raiseEvent(new StopRecordingEvent());

			// Respond
			std::string responseString = "THANKS";
			zmq::message_t response(responseString.data(), responseString.size());
			registrar.send(response, zmq::send_flags::none);
		}
		else if (requestString == "REP_SPEED_UP")
		{
			EventManager::getInstance()->raiseEvent(new ChangeReplaySpeedEvent(2.0));

			// Respond
			std::string responseString = "THANKS";
			zmq::message_t response(responseString.data(), responseString.size());
			registrar.send(response, zmq::send_flags::none);
		}
		else if (requestString == "REP_SPEED_DOWN")
		{
			EventManager::getInstance()->raiseEvent(new ChangeReplaySpeedEvent(0.5));

			// Respond
			std::string responseString = "THANKS";
			zmq::message_t response(responseString.data(), responseString.size());
			registrar.send(response, zmq::send_flags::none);
		}
		else if (game.getReplaySystem()->isReplaying())
		{
			// Do Nothing
			
			// Respond
			std::string responseString = "THANKS";
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
			std::bitset<3> keys;
			
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
				int i = 0;
				while (std::getline(inputKeyStream, key, ','))
				{
					if (key == "true")
					{
						keys[i] = true;
					}
					else if (key == "false")
					{
						keys[i] = false;
					}
					i++;
				}
				if (keys != InputManager::getInstance()->getInputs(playerNumber))
				{
					auto inputEvent = new InputEvent(playerNumber, keys);
					EventManager::getInstance()->raiseEvent(inputEvent);
				}
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
