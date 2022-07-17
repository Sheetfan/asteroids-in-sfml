#include "InputManager.h"

namespace buzi {
	InputManager::InputManager() {
		controller = new Controller(0);
	}
	bool InputManager::inSpriteClicked(sf::Sprite object, sf::Mouse::Button button,sf::RenderWindow &window)
	{
		if (sf::Mouse::isButtonPressed(button)) {
			sf::IntRect tempRect(object.getPosition().x, object.getPosition().y, object.getGlobalBounds().width, object.getGlobalBounds().height);

			if (tempRect.contains(sf::Mouse::getPosition(window))) {
				return true;
			}
		}
		return false;
	}

	sf::Vector2i InputManager::getMousePosition(sf::RenderWindow& window) {
		return sf::Mouse::getPosition(window);
	}
	Controller InputManager::getController(){
		return *controller;
	}
}
