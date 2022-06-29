#include "AssetManager.h"

void AssetManager::setTexture(std::string textureName, std::string fileName){
	sf::Texture texture;
	if (!texture.loadFromFile(fileName)) {
		throw "Can't find file name";
	}
	textures[textureName] = texture;
}

sf::Texture& AssetManager::getTexture(std::string textureName) {
	return textures[textureName];
}
