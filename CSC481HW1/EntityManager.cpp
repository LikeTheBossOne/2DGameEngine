#include "EntityManager.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include "Entity.h"
#include "Player.h"

EntityManager::EntityManager()
{
	_entities = std::map<int, Entity*>();
	_players = std::map<int, Entity*>();
	_myPlayer = nullptr;
}

void EntityManager::setEntity(int GUID, Entity* entity)
{
	_entities[GUID] = entity;
}

void EntityManager::setPlayer(int GUID, Entity* entity)
{
	_players[GUID] = entity;
}

void EntityManager::setMyPlayer(Entity* player)
{
	_myPlayer = player;
}

/**
 * Render Entities then Player
 */
void EntityManager::draw(sf::RenderWindow& window, std::mutex& myPlayerLock, std::mutex& playersLock, std::mutex& entitiesLock)
{
	entitiesLock.lock();
	for (std::pair<int, Entity*> ePair : _entities)
	{
		window.draw(*ePair.second);
	}
	entitiesLock.unlock();
	playersLock.lock();
	for (std::pair<int, Entity*> ePair : _players)
	{
		window.draw(*ePair.second);
	}
	playersLock.unlock();
	myPlayerLock.lock();
	window.draw(*_myPlayer);
	myPlayerLock.unlock();
}

