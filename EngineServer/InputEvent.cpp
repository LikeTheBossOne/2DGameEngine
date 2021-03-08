#include "InputEvent.h"

InputEvent::InputEvent(int playerGUID, std::bitset<3> inputs) : Event(2, 0)
{
	this->playerGUID = playerGUID;
	this->inputs = inputs;
}
