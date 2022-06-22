#include "Game.h"

Game::Game(sf::Vector2f windowSize):windowSize(windowSize) {
	ship.setObj(texture,windowSize);
}

void Game::update(sf::RenderWindow& window, float dt) {
	window.clear(sf::Color::Black);
	ship.physics(dt);
	this->wrap(window,ship);
}

void Game::eventHandler(sf::RenderWindow& window) {
	sf::Event event;

	while (window.pollEvent(event)) {
		if (event.type == event.Closed) {
			window.close();
		}

	}
}

void Game::wrap(sf::RenderWindow& window, class SpaceObj& obj) {

	if (obj.getPosition().x <= 0.f - obj.getGlobalBounds().width / 2.f) {
		obj.setPosition(windowSize.x + obj.getGlobalBounds().width / 2.f, obj.getPosition().y);
	}
	else if (obj.getPosition().x  >= windowSize.x + obj.getGlobalBounds().width / 2.f) {
		obj.setPosition(0.f - obj.getGlobalBounds().width / 2.f, obj.getPosition().y);
	}

	if (obj.getPosition().y <= 0.f - obj.getGlobalBounds().height / 2.f) {
		obj.setPosition(obj.getPosition().x, windowSize.y + obj.getGlobalBounds().height / 2.f);
	}
	else if (obj.getPosition().y >= windowSize.y + obj.getGlobalBounds().height / 2.f) {
		obj.setPosition(obj.getPosition().x, 0.f - obj.getGlobalBounds().height / 2.f);
	}
}

void Game::render(sf::RenderWindow& window) {
	window.draw(ship);
	window.display();
}
void Game::mainLoop(sf::RenderWindow& window) {
	while (window.isOpen()) {
		dt = clock.restart().asSeconds();
		this->eventHandler(window);
		this->update(window, dt);
		this->render(window);
	}
}