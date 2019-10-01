#include "Game.h"
#include "Settings.h"
#include <zmq.hpp>
#include <thread>
#include "EntityManager.h"
#include "Entity.h"

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
			bool texture;
			float textureX;
			float textureY;
			float textureWidth;
			float textureHeight;
			std::string textureName;

			std::string field;
			std::istringstream entityStream(entityLine);

			
			// _GUID
			std::getline(entityStream, field, ',');
			guid = std::stoi(field);

			// TYPE
			std::getline(entityStream, field, ',');
			type = field;
			
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
			height= std::stof(field);

			// Has Texture?
			std::getline(entityStream, field, ',');
			if (field == "true") texture = true;
			else texture = false;
			if (texture)
			{
				// TEXTURE X
				std::getline(entityStream, field, ',');
				textureX = std::stof(field);

				// TEXTURE Y
				std::getline(entityStream, field, ',');
				textureY = std::stof(field);

				// TEXTURE WIDTH
				std::getline(entityStream, field, ',');
				textureWidth = std::stof(field);

				// TEXTURE HEIGHT
				std::getline(entityStream, field, ',');
				textureHeight = std::stof(field);

				// TEXTURE NAME
				std::getline(entityStream, field, ',');
				textureName = field;
			}


			// Build entity
			if (game.getEntityManager()->getMyPlayer() != nullptr
				&& guid == game.getEntityManager()->getMyPlayer()->getGUID())
			{
				myPlayerLock.lock();
				
				Entity* myPlayer = game.getEntityManager()->getMyPlayer();
				myPlayer->setPosition(x, y);
				myPlayer->setSize(sf::Vector2f(width, height));
				if (texture)
				{
					myPlayer->setTextureRect(sf::IntRect(textureX, textureY, textureWidth, textureHeight));
				}
				else
				{
					myPlayer->setFillColor(sf::Color(150, 50, 250));
				}
				
				myPlayerLock.unlock();
			}
			else if (game.getEntityManager()->getPlayers().count(guid) == 1)
			{
				playersLock.lock();
				
				Entity* player = game.getEntityManager()->getPlayers().at(guid);
				player->setPosition(x, y);
				player->setSize(sf::Vector2f(width, height));
				if (texture)
				{
					player->setTextureRect(sf::IntRect(textureX, textureY, textureWidth, textureHeight));
				}
				else
				{
					player->setFillColor(sf::Color(150, 50, 250));
				}

				playersLock.unlock();
			}
			else if (game.getEntityManager()->getEntities().count(guid) == 1) 
			{
				entitiesLock.lock();
				
				Entity* entity = game.getEntityManager()->getEntities().at(guid);
				entity->setPosition(x, y);
				entity->setSize(sf::Vector2f(width, height));
				if (texture)
				{
					entity->setTextureRect(sf::IntRect(textureX, textureY, textureWidth, textureHeight));
				}
				else
				{
					entity->setFillColor(sf::Color(150, 50, 250));
				}

				entitiesLock.unlock();
			}
			else // Doesn't exist yet
			{
				if (guid == game.getPlayerNumber()) // This is the first time myPlayer is being instantiated
				{
					myPlayerLock.lock();
					
					Entity* player = new Entity(&game, guid, sf::Vector2f(width, height));
					player->setPosition(x, y);
					if (texture)
					{
						player->setTextureRect(sf::IntRect(textureX, textureY, textureWidth, textureHeight));
						player->setTexture(game.getTexturesMap()[textureName]);
					}
					else
					{
						player->setFillColor(sf::Color(150, 50, 250));
					}
					game.getEntityManager()->setMyPlayer(player);

					myPlayerLock.unlock();
					if (!game.getShouldStartYet())
					{
						game.setShouldStartYet(true);
					}
				}
				else if (type == "player") // new player joined
				{
					playersLock.lock();
					
					Entity* player = new Entity(&game, guid, sf::Vector2f(width, height));
					player->setPosition(x, y);
					if (texture)
					{
						player->setTextureRect(sf::IntRect(textureX, textureY, textureWidth, textureHeight));
						player->setTexture(game.getTexturesMap()[textureName]);
					}
					else
					{
						player->setFillColor(sf::Color(150, 50, 250));
					}
					game.getEntityManager()->setPlayer(guid, player);

					playersLock.unlock();
				}
				else if (type == "entity")
				{
					entitiesLock.lock();
					
					Entity* entity = new Entity(&game, guid, sf::Vector2f(width, height));
					entity->setPosition(x, y);
					if (texture)
					{
						entity->setTextureRect(sf::IntRect(textureX, textureY, textureWidth, textureHeight));
						entity->setTexture(game.getTexturesMap()[textureName]);
					}
					else
					{
						entity->setFillColor(sf::Color(150, 50, 250));
					}
					game.getEntityManager()->setEntity(guid, entity);

					entitiesLock.unlock();
				}
			}
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
	const int playerNumber = std::stoi(std::string(static_cast<char*>(firstResponse.data()), firstResponse.size()));


	std::mutex myPlayerLock;
	std::mutex playersLock;
	std::mutex entitiesLock;
	// Start Game
	Game game(playerNumber);

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
