#pragma once
#include <bitset>
#include <map>

class GameObject;

class InputManager
{
public:
	static InputManager* getInstance();

	void setInputs(int GUID, std::bitset<3> inputs) { _inputs[GUID] = inputs; }
	
	std::bitset<3> getInputs(int GUID);
	std::map<int, std::bitset<3>> getAllInputs() { return _inputs; };
private:
	InputManager();
	static InputManager* _instance;

	std::map<int, std::bitset<3>> _inputs;
};

