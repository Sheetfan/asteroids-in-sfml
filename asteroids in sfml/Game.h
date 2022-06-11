#pragma once
#include "Ship.h"
class Game{
	sf::Vector2f windowSize;
	Ship ship;
	sf::Clock clock;
	float dt = 0.0;
public:

	Game(sf::Vector2f windowSize);

	void update(sf::RenderWindow& window, float dt);

	void eventHandler(sf::RenderWindow& window);

	void wrap(sf::RenderWindow& window, class SpaceObj& obj);

	void render(sf::RenderWindow& window);

	void mainLoop(sf::RenderWindow& window);

	
};

