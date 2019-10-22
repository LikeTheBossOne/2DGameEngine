#pragma once
#include <map>
#include <vector>
#include "Inputs.h"

class GameObject;

class InputManager
{
public:
	InputManager();

	static InputManager* getInstance();

	void setInputs(int GUID, std::vector<bool> inputs);

	std::vector<bool> getInputs(int GUID);
private:
	static InputManager* _instance;

	std::map<int, std::vector<bool>> _inputs;
};

