#include "ResourceManager.h"

ResourceManager::ResourceManager(Game* game)
{
	_game = game;

	_texturesMap = std::unordered_map<std::string, sf::Texture*>();
	_fontsMap = std::unordered_map<std::string, sf::Font*>();
}

void ResourceManager::addTexture(std::string name, sf::Texture* texture)
{
	_texturesMap[name] = texture;
}

void ResourceManager::addFont(std::string name, sf::Font* font)
{
	_fontsMap[name] = font;
}
