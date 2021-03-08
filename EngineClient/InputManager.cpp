#include "InputManager.h"

InputManager* InputManager::_instance;

InputManager::InputManager()
{
	_inputs = std::map<int, std::bitset<3>>();
}

InputManager* InputManager::getInstance()
{
	if (_instance == nullptr)
	{
		_instance = new InputManager();
	}

	return _instance;
}

std::bitset<3> InputManager::getInputs(int GUID)
{
	return _inputs[GUID];
}
