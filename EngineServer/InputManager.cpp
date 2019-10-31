#include "InputManager.h"
#include "GameObject.h"
#include "PlayerInputComponent.h"

InputManager* InputManager::_instance;

InputManager::InputManager()
{
	_inputs = std::map<int, std::vector<bool>>();
}

InputManager* InputManager::getInstance()
{
	if (_instance == nullptr)
	{
		_instance = new InputManager();
	}

	return _instance;
}

void InputManager::setInputs(int GUID, std::vector<bool> inputs)
{
	_inputs[GUID] = inputs;
}

std::vector<bool> InputManager::getInputs(int GUID)
{
	return _inputs[GUID];
}
