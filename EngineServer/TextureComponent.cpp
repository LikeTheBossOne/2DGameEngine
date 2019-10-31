#include "TextureComponent.h"
#include "PlayerInputComponent.h"

TextureComponent::TextureComponent(GameObject* gameObject, std::string textureName) : GenericComponent(gameObject)
{
	_textureName = textureName;

	_animationNumber = 0;
}

void TextureComponent::update(int deltaTime)
{
}
