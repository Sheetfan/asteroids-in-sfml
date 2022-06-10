#include <iostream>
#include "SFML/Audio.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"

sf::Vector2f windowSize = sf::Vector2f(1200.f, 1000.f);

int main(){
	sf::RenderWindow window(sf::VideoMode(windowSize.x, windowSize.y), "asteroids", sf::Style::Close);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == event.Closed) {
				window.close();
			}

		}
		
		window.clear();

		window.display();
	}
}

