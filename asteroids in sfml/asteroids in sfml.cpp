#include <iostream>
#include "SFML/Audio.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "Asteroids.h"
#include "Saucer.h"
#include "Ship.h"
#include "Game.h"

sf::Vector2f windowSize = sf::Vector2f(1200.f, 1000.f);

int main(){
	
	sf::RenderWindow window(sf::VideoMode(windowSize.x, windowSize.y), "asteroids", sf::Style::Close);
	//window.setFramerateLimit(60);
	Game game(windowSize);
	game.mainLoop(window);
}

