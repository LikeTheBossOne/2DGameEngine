#pragma once
#include <string>
#include "GenericComponent.h"

class PlayerInputComponent;

class TextureComponent: public GenericComponent
{
public:
	TextureComponent(GameObject* gameObject, std::string textureName);

	void update(int deltaTime) override;
	ComponentTypes getType() override { return ComponentTypes::TextureComponent; };

	void setTextureName(std::string textureName) { _textureName = textureName; }
	
	std::string getTextureName() { return _textureName; }

	int getAnimationNumber() { return _animationNumber; }
private:
	std::string _textureName;
	int _animationNumber;
};

