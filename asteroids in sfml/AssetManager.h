#pragma once

#include "SFML/Graphics.hpp"
#include <map>
class AssetManager {
	std::map<std::string, sf::Texture> textures;

	AssetManager() {}

	void setTexture(std::string textureName, std::string fileName);

	sf::Texture& getTexture(std::string textureName);

};
