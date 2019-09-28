#include "EntityManager.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include "Entity.h"
#include "Player.h"

EntityManager::EntityManager()
{
	_entities = std::vector<Entity*>();
	_player = nullptr;
}

void EntityManager::setPlayer(Player* player)
{
	_player = player;
}

void EntityManager::addEntity(Entity* entity)
{
	_entities.emplace_back(entity);
}

/**
 * Update Entities then Player
 */
void EntityManager::tick(int deltaTime)
{
	for (Entity* entity : _entities)
	{
		entity->tick(deltaTime);
	}
	_player->tick(deltaTime);
}

/**
 * Render Entities then Player
 */
void EntityManager::draw(sf::RenderWindow& window)
{
	for (Entity* entity : _entities)
	{
		window.draw(*entity);
	}
	window.draw(*_player);
}

