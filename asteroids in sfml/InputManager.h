#pragma once
#include "SFML/Graphics.hpp"

namespace buzi {
	class InputManager{

	public:
		InputManager() {}
		~InputManager() {}
		
		bool inSpriteClicked(sf::Sprite object, sf::Mouse::Button button, sf::RenderWindow& window);

		sf::Vector2i getMousePosition(sf::RenderWindow& window);
	};

}

