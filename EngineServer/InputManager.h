#pragma once
#include <map>
#include <vector>
#include <mutex>


class Game;

class InputManager
{
public:
	InputManager(Game* game);

	void addPlayer(int GUID);

	void setPlayerKeyPressed(int GUID, std::vector<bool> keys);
	std::vector<bool> getPlayerKeysPressed(int GUID);
	
private:
	Game* _game;

	std::map<int, std::vector<bool>> _playerKeysPressed;

	std::mutex _keyLock;
};

