#pragma once
#include "SFML/Graphics.hpp"
#include "Controller.h"
#include <array>

namespace buzi {
	class InputManager{
		Controller *controller;

	public:
		InputManager();
		~InputManager() {}
		
		bool inSpriteClicked(sf::Sprite object, sf::Mouse::Button button, sf::RenderWindow& window);

		
		sf::Vector2i getMousePosition(sf::RenderWindow& window);
		Controller getController();
	};

}

