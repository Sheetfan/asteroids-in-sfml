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

void AssetManager::setFont(std::string fontName, std::string fileName){
	sf::Font font;
	if (!font.loadFromFile(fileName)) {
		throw "Can't find file name";
	}
	fonts[fontName] = font;
}

sf::Font& AssetManager::getFont(std::string fontName){
	return fonts[fontName];
}
