#include "InputManager.h"
#include "GameObject.h"
#include "PlayerInputComponent.h"
#include "EventManager.h"
#include "InputEvent.h"

InputManager* InputManager::_instance;

InputManager::InputManager()
{
	_inputs = std::map<int, std::bitset<3>>();

	EventManager::getInstance()->registerFor(this, "Input");
}

InputManager* InputManager::getInstance()
{
	if (_instance == nullptr)
	{
		_instance = new InputManager();
	}

	return _instance;
}

void InputManager::onEvent(Event* e)
{
	if (e->getType() == "Input")
	{
		handleInputEvent(static_cast<InputEvent*>(e));
	}
}

void InputManager::handleInputEvent(InputEvent* e)
{
	_inputs[e->playerGUID] = e->inputs;
}

std::bitset<3> InputManager::getInputs(int GUID)
{
	return _inputs[GUID];
}
