#pragma once
#include <string>
#include "GenericComponent.h"
#include "SFML/Graphics.hpp"

class PlayerInputComponent;

class TextureComponent : public GenericComponent
{
public:
	TextureComponent(GameObject* gameObject, sf::Texture* texture);

	void update(int deltaTime) override;
	ComponentTypes getType() override { return ComponentTypes::TextureComponent; };

	
private:
	sf::Texture* _texture;
};
