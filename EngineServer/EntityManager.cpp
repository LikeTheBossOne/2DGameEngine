#include "EntityManager.h"
#include "Entity.h"
#include "Player.h"
#include "Game.h"
#include "InputManager.h"

EntityManager::EntityManager(Game* game)
{
	_game = game;
	
	_entities = std::map<int, Entity*>();
	_players = std::map<int, Player*>();
}

void EntityManager::addPlayer(Player* player)
{
	_playerLock.lock();
	
	_players.emplace(player->getGUID(), player);
	_game->getInputManager()->addPlayer(player->getGUID());
	
	_playerLock.unlock();
}

void EntityManager::addEntity(Entity* entity)
{
	_entities.emplace(entity->getGUID(), entity);
}

void EntityManager::deletePlayer(int GUID)
{
	_players.erase(GUID);
}

/**
 * Update Entities then Player
 */
void EntityManager::tick(int deltaTime)
{
	for (std::pair<int, Entity*> ePair : _entities)
	{
		ePair.second->tick(deltaTime);
	}
	for (std::pair<int, Player*> pPair : _players)
	{
		pPair.second->tick(deltaTime);
	}
}
