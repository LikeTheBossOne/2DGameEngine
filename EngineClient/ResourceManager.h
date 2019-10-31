#pragma once
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>
#include <unordered_map>
class Game;

class ResourceManager
{
public:
	ResourceManager(Game* game);

	void addTexture(std::string name, sf::Texture* texture);
	void addFont(std::string name, sf::Font* font);
	void addTextureAnimations(std::string name, std::vector<sf::IntRect> animationsRects);
	
	std::unordered_map<std::string, sf::Texture*> getTexturesMap() { return _texturesMap; }
	std::unordered_map<std::string, sf::Font*> getFontsMap() { return _fontsMap; }
	std::unordered_map<std::string, std::vector<sf::IntRect>> getTextureAnimationsMap() { return _textureAnimationsMap; }
	sf::IntRect getTextureRectForAnimation(std::string name, int animation);
private:
	Game* _game;

	std::unordered_map<std::string, sf::Texture*> _texturesMap;
	std::unordered_map<std::string, sf::Font*> _fontsMap;
	std::unordered_map<std::string, std::vector<sf::IntRect>> _textureAnimationsMap;
};

