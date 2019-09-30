#include "InputManager.h"

InputManager::InputManager(Game* game)
{
	_game = game;

	_playerKeysPressed = std::map<int, std::vector<bool>>();
}

void InputManager::addPlayer(int GUID)
{
	std::vector<bool> inputs = { false, false, false };

	_keyLock.lock();
	_playerKeysPressed.emplace(GUID, inputs);
	_keyLock.unlock();
}

void InputManager::setPlayerKeyPressed(int GUID, std::vector<bool> keys)
{
	_playerKeysPressed.at(GUID) = keys;
}


std::vector<bool> InputManager::getPlayerKeysPressed(int GUID)
{
	return _playerKeysPressed.at(GUID);
}
