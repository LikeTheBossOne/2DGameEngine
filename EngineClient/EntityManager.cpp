#include "EntityManager.h"
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "Player.h"
#include "TransformComponent.h"
#include "GameCamera.h"
#include "SideBoundary.h"
#include "SideBoundaryComponent.h"
#include "Settings.h"
#include "InputManager.h"
#include <iostream>

EntityManager::EntityManager(Game* game)
{
	_game = game;

	_gameCamera = new GameCamera();
	
	_entities = std::map<int, GameObject*>();
	_sideBoundaries = std::map<int, SideBoundary*>();
	_players = std::map<int, Player*>();
	_myPlayer = nullptr;
}

void EntityManager::setEntity(int GUID, GameObject* entity)
{
	_entities[GUID] = entity;
}

void EntityManager::addSideBoundary(int GUID, SideBoundary* sideBoundary)
{
	_sideBoundaries[GUID] = sideBoundary;
}

void EntityManager::setPlayer(int GUID, Player* entity)
{
	_players[GUID] = entity;
}

void EntityManager::setMyPlayer(Player* player)
{
	_myPlayer = player;
}

void EntityManager::deletePlayer(int GUID, std::mutex& playersLock)
{
	playersLock.lock();
	_players.erase(GUID);
	playersLock.unlock();
}

void EntityManager::update(std::mutex& myPlayerLock)
{
	// Detect Collisions with SideBoundaries
	if (_myPlayer != nullptr)
	{
		auto transform = _myPlayer->getTransform();

		while (transform->getPositionX() + transform->getWidth() < _gameCamera->getOffsetX() && transform->getPositionX() > 0)
		{
			_gameCamera->move(-WINDOW_WIDTH, 0);
		}
		for (std::pair<int, SideBoundary*> boundary : _sideBoundaries)
		{
			auto boundaryTransform = boundary.second->getTransform();
			auto sideBoundary = dynamic_cast<SideBoundaryComponent*>(boundary.second->getComponent(ComponentTypes::SideBoundaryComponent));
			
			// Check collision
			if (transform->getPositionX() + transform->getWidth() > boundaryTransform->getPositionX()
				&& transform->getPositionX() < boundaryTransform->getPositionX())
			{
				auto inputs = InputManager::getInstance()->getInputs(_myPlayer->getGUID());
				std::cout << inputs.to_string() << std::endl;
				// if right of boundary
				if (_gameCamera->getOffsetX() >= boundaryTransform->getPositionX() && inputs[0])
				{
					_gameCamera->move(-WINDOW_WIDTH, 0);
				}
				// if right of boundary
				else if (_gameCamera->getOffsetX() < boundaryTransform->getPositionX() && inputs[1])
				{
					_gameCamera->setOffsetX(boundaryTransform->getPositionX());
				}
				break;
			}
		}
	}
}

/**
 * Render Entities then Player
 */
void EntityManager::draw(sf::RenderWindow& window, std::mutex& myPlayerLock, std::mutex& playersLock, std::mutex& entitiesLock)
{
	entitiesLock.lock();
	for (std::pair<int, GameObject*> ePair : _entities)
	{
		// Only render if visible
		if (ePair.second->getTransform()->isVisible())
		{
			sf::RectangleShape obj = sf::RectangleShape(*ePair.second->getSFRectangleShape());
			obj.move(-_gameCamera->getOffsetX(), -_gameCamera->getOffsetY());
			window.draw(obj);
		}
	}
	entitiesLock.unlock();
	playersLock.lock();
	for (std::pair<int, Player*> ePair : _players)
	{
		// Don't check visible on players (maybe in future)
		sf::RectangleShape obj = sf::RectangleShape(*ePair.second->getSFRectangleShape());
		obj.move(-_gameCamera->getOffsetX(), -_gameCamera->getOffsetY());
		window.draw(obj);
	}
	playersLock.unlock();
	myPlayerLock.lock();
	sf::RectangleShape obj = sf::RectangleShape(*_myPlayer->getSFRectangleShape());
	obj.move(-_gameCamera->getOffsetX(), -_gameCamera->getOffsetY());
	window.draw(obj);
	myPlayerLock.unlock();
}

