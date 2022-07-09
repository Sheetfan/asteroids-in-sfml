#pragma once

#include "SFML/Graphics.hpp"
#include <map>
class AssetManager {
	std::map<std::string, sf::Texture> textures;
	std::map<std::string, sf::Font> fonts;
public:
	AssetManager() {}

	void setTexture(std::string textureName, std::string fileName);
	sf::Texture& getTexture(std::string textureName);

	void setFont(std::string fontName, std::string fileName);
	sf::Font& getFont(std::string fontName);

};
