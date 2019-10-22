#include "ResourceManager.h"
#include <utility>

ResourceManager::ResourceManager(Game* game)
{
	_game = game;

	_texturesMap = std::unordered_map<std::string, sf::Texture*>();
	_fontsMap = std::unordered_map<std::string, sf::Font*>();
	_textureAnimationsMap = std::unordered_map<std::string, std::vector<sf::IntRect>>();
}

void ResourceManager::addTextureAnimations(std::string name, std::vector<sf::IntRect> animationsRects)
{
	_textureAnimationsMap[name] = std::move(animationsRects);
}

sf::IntRect ResourceManager::getTextureRectForAnimation(std::string name, int animation)
{
	return _textureAnimationsMap[name][animation];
}

void ResourceManager::addTexture(std::string name, sf::Texture* texture)
{
	_texturesMap[name] = texture;
}

void ResourceManager::addFont(std::string name, sf::Font* font)
{
	_fontsMap[name] = font;
}
