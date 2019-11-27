#include "TextureComponent.h"
#include "PlayerInputComponent.h"

TextureComponent::TextureComponent(GameObject* gameObject, std::string textureName) : GenericComponent(gameObject)
{
	_textureName = textureName;

	_animationNumber = 0;
}

TextureComponent::TextureComponent(const TextureComponent& other, GameObject* gameObject) : GenericComponent(gameObject)
{
	_textureName = other._textureName;
	_animationNumber = other._animationNumber;
}

void TextureComponent::update(int deltaTime)
{
}
