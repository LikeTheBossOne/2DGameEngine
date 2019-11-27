#include "Game.h"
#include <zmq.hpp>
#include <thread>
#include "EntityManager.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "Player.h"
#include "StaticPlatform.h"
#include "PatternPlatform.h"
#include "SideBoundary.h"
#include "TransformComponent.h"
#include <bitset>
#include "InputManager.h"

const std::string REQREP_PORT = "tcp://localhost:5555";
const std::string PUBSUB_PORT = "tcp://localhost:5560";

void subscriberCommunication(Game& game, zmq::context_t& context, std::mutex& myPlayerLock, std::mutex& playersLock, std::mutex& entitiesLock)
{
	zmq::socket_t subscriber(context, ZMQ_SUB);
	subscriber.connect(PUBSUB_PORT);
	subscriber.setsockopt(ZMQ_SUBSCRIBE, "", 0);
	
	while (!game.getShouldEnd())
	{
		zmq::message_t subMessage;
		subscriber.recv(subMessage);

		auto subString = std::string(static_cast<char*>(subMessage.data()), subMessage.size());

		// Create list to potentially delete players who have DC'd
		auto playersToDelete = game.getEntityManager()->getPlayers();

		
		std::istringstream subStream(subString);

		std::string entityLine;
		while (std::getline(subStream, entityLine))
		{
			bool remove;
			int guid;
			std::string type;
			float x;
			float y;
			float width;
			float height;
			std::string texColorType;
			bool texture;
			bool color;
			std::string textureName;
			int colorR;
			int colorG;
			int colorB;
			int textureAnimation;
			bool leftPressed;
			bool rightPressed;
			bool upPressed;
			

			std::string field;
			std::istringstream entityStream(entityLine);

			
			// _GUID
			std::getline(entityStream, field, ',');
			guid = std::stoi(field);

			// TYPE
			std::getline(entityStream, field, ',');
			type = field;

			if (type == "SideBoundary")
			{
				// X
				std::getline(entityStream, field, ',');
				x = std::stof(field);

				// SCENE SHIFT WIDTH
				std::getline(entityStream, field, ',');
				width = std::stof(field);
			}
			else
			{
				// X
				std::getline(entityStream, field, ',');
				x = std::stof(field);

				// Y
				std::getline(entityStream, field, ',');
				y = std::stof(field);

				// WIDTH
				std::getline(entityStream, field, ',');
				width = std::stof(field);

				// HEIGHT
				std::getline(entityStream, field, ',');
				height = std::stof(field);

				// Has Texture?
				std::getline(entityStream, field, ',');
				texColorType = field;

				texture = texColorType == "Texture";
				color = texColorType == "Color";
				if (texture)
				{
					// TEXTURE NAME
					std::getline(entityStream, field, ',');
					textureName = field;

					// TEXTURE ANIMATION NUMBER
					std::getline(entityStream, field, ',');
					textureAnimation = std::stoi(field);
				}
				else if (color)
				{
					// R
					std::getline(entityStream, field, ',');
					colorR = std::stoi(field);

					// G
					std::getline(entityStream, field, ',');
					colorG = std::stoi(field);

					// B
					std::getline(entityStream, field, ',');
					colorB = std::stoi(field);
				}

				if (type == "Player")
				{
					std::bitset<3> keys;
					
					std::getline(entityStream, field, ',');
					keys[0] = field == "1";

					std::getline(entityStream, field, ',');
					keys[1] = field == "1";

					std::getline(entityStream, field, ',');
					keys[2] = field == "1";

					InputManager::getInstance()->setInputs(guid, keys);
				}
			}
			
			// Build entity
			if (game.getEntityManager()->getMyPlayer() != nullptr
				&& guid == game.getEntityManager()->getMyPlayer()->getGUID())
			{
				myPlayerLock.lock();
				
				Player* myPlayer = game.getEntityManager()->getMyPlayer();
				myPlayer->getSFRectangleShape()->setPosition(x, y);
				myPlayer->getTransform()->setPositionX(x);
				myPlayer->getTransform()->setPositionY(y);
				myPlayer->getSFRectangleShape()->setSize(sf::Vector2f(width, height));
				if (texture)
				{
					myPlayer->getSFRectangleShape()->setTextureRect(game.getResourceManager()->getTextureRectForAnimation(textureName, textureAnimation));
				}
				else if (color)
				{
					myPlayer->getSFRectangleShape()->setFillColor(sf::Color(colorR, colorG, colorB));
				}
				else
				{
					myPlayer->getSFRectangleShape()->setFillColor(sf::Color(150, 50, 250));
				}
				
				myPlayerLock.unlock();
			}
			else if (game.getEntityManager()->getPlayers().count(guid) == 1)
			{
				playersLock.lock();
				
				Player* player = game.getEntityManager()->getPlayers().at(guid);
				player->getSFRectangleShape()->setPosition(x, y);
				player->getTransform()->setPositionX(x);
				player->getTransform()->setPositionY(y);
				player->getSFRectangleShape()->setSize(sf::Vector2f(width, height));
				if (texture)
				{
					player->getSFRectangleShape()->setTextureRect(game.getResourceManager()->getTextureRectForAnimation(textureName, textureAnimation));
				}
				else if (color)
				{
					player->getSFRectangleShape()->setFillColor(sf::Color(colorR, colorG, colorB));
				}
				else
				{
					player->getSFRectangleShape()->setFillColor(sf::Color(150, 50, 250));
				}

				playersLock.unlock();
			}
			else if (game.getEntityManager()->getEntities().count(guid) == 1) 
			{
				
				entitiesLock.lock();
				GameObject* entity = game.getEntityManager()->getEntities().at(guid);
				entity->getSFRectangleShape()->setPosition(x, y);
				entity->getTransform()->setPositionX(x);
				entity->getTransform()->setPositionY(y);
				entity->getSFRectangleShape()->setSize(sf::Vector2f(width, height));
				if (texture)
				{
					entity->getSFRectangleShape()->setTextureRect(game.getResourceManager()->getTextureRectForAnimation(textureName, textureAnimation));
				}
				else if (color)
				{
					entity->getSFRectangleShape()->setFillColor(sf::Color(colorR, colorG, colorB));
				}
				else
				{
					entity->getSFRectangleShape()->setFillColor(sf::Color(150, 50, 250));
				}

				entitiesLock.unlock();
			}
			else if (game.getEntityManager()->getSideBoundaries().count(guid) == 1)
			{
				// Do nothing if boundary already exists
			}
			else // Doesn't exist yet
			{
				if (guid == game.getPlayerNumber()) // This is the first time myPlayer is being instantiated
				{
					Player* player = new Player(guid, sf::FloatRect(x, y, width, height));
					if (texture)
					{
						player->getSFRectangleShape()->setTextureRect(game.getResourceManager()->getTextureRectForAnimation(textureName, textureAnimation));
						player->getSFRectangleShape()->setTexture(game.getResourceManager()->getTexturesMap()[textureName]);
					}
					else if (color)
					{
						player->getSFRectangleShape()->setFillColor(sf::Color(colorR, colorG, colorB));
					}
					else
					{
						player->getSFRectangleShape()->setFillColor(sf::Color(150, 50, 250));
					}
					
					myPlayerLock.lock();
					game.getEntityManager()->setMyPlayer(player);
					myPlayerLock.unlock();
					
					if (!game.getShouldStartYet())
					{
						game.setShouldStartYet(true);
					}
				}
				else if (type == "Player") // new player joined
				{
					Player* player = new Player(guid, sf::FloatRect(x, y, width, height));
					if (texture)
					{
						player->getSFRectangleShape()->setTextureRect(game.getResourceManager()->getTextureRectForAnimation(textureName, textureAnimation));
						player->getSFRectangleShape()->setTexture(game.getResourceManager()->getTexturesMap()[textureName]);
					}
					else if (color)
					{
						player->getSFRectangleShape()->setFillColor(sf::Color(colorR, colorG, colorB));
					}
					else
					{
						player->getSFRectangleShape()->setFillColor(sf::Color(150, 50, 250));
					}

					playersLock.lock();
					game.getEntityManager()->setPlayer(guid, player);
					playersLock.unlock();
				}
				else if (type == "StaticPlatform")
				{
					entitiesLock.lock();
					
					StaticPlatform* entity = new StaticPlatform(guid, sf::FloatRect(x, y, width, height));
					if (texture)
					{
						entity->getSFRectangleShape()->setTextureRect(game.getResourceManager()->getTextureRectForAnimation(textureName, textureAnimation));
						entity->getSFRectangleShape()->setTexture(game.getResourceManager()->getTexturesMap()[textureName]);
					}
					else if (color)
					{
						entity->getSFRectangleShape()->setFillColor(sf::Color(colorR, colorG, colorB));
					}
					else
					{
						entity->getSFRectangleShape()->setFillColor(sf::Color(150, 50, 250));
					}
					game.getEntityManager()->setEntity(guid, entity);

					entitiesLock.unlock();
				}
				else if (type == "PatternPlatform")
				{
					PatternPlatform* entity = new PatternPlatform(guid, sf::FloatRect(x, y, width, height));
					if (texture)
					{
						entity->getSFRectangleShape()->setTextureRect(game.getResourceManager()->getTextureRectForAnimation(textureName, textureAnimation));
						entity->getSFRectangleShape()->setTexture(game.getResourceManager()->getTexturesMap()[textureName]);
					}
					else if (color)
					{
						entity->getSFRectangleShape()->setFillColor(sf::Color(colorR, colorG, colorB));
					}
					else
					{
						entity->getSFRectangleShape()->setFillColor(sf::Color(150, 50, 250));
					}
					
					entitiesLock.lock();
					game.getEntityManager()->setEntity(guid, entity);
					entitiesLock.unlock();
				}
				else if (type == "SideBoundary")
				{
					auto boundary = new SideBoundary(guid, x, width);

					game.getEntityManager()->addSideBoundary(guid, boundary);
				}
			}

			// remove from toDelete list
			playersToDelete.erase(guid);
		}
		for (auto pair : playersToDelete)
		{
			game.getEntityManager()->deletePlayer(pair.first, playersLock);
		}
	}
	subscriber.close();
}

int main()
{
	// Initiate Connection to server
	zmq::context_t context(1);
	zmq::socket_t socket(context, ZMQ_REQ);
	socket.connect(REQREP_PORT);

	std::string firstMessageString = "OPEN";
	zmq::message_t firstMessage(firstMessageString.data(), firstMessageString.size());
	socket.send(firstMessage, zmq::send_flags::none);

	zmq::message_t firstResponse;
	socket.recv(firstResponse);

	// Get data about this client/player
	auto firstString = std::string(static_cast<char*>(firstResponse.data()), firstResponse.size());
	std::istringstream firstStream(firstString);
	std::string firstLine;

	std::getline(firstStream, firstLine, ' ');
	const int playerNumber = std::stoi(firstLine);

	std::getline(firstStream, firstLine, ' ');
	const int clientNumber = std::stoi(firstLine);


	std::mutex myPlayerLock;
	std::mutex playersLock;
	std::mutex entitiesLock;
	// Start Game
	Game game(clientNumber, playerNumber);

	std::thread subscriberThread(
		subscriberCommunication,
		std::ref(game),
		std::ref(context),
		std::ref(myPlayerLock),
		std::ref(playersLock),
		std::ref(entitiesLock)
	);


	
	game.run(socket, myPlayerLock, playersLock, entitiesLock);

	subscriberThread.join();
	return 0;
}
