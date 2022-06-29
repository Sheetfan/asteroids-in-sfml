#include "GameState.h"
#include "DEFINITIONS.h"
#include <iostream>

namespace buzi {
	GameState::GameState(GameDataRef data) :data(data) {}

	void GameState::init() {
		data->assets.setTexture("Ship", SHIP_FILE_PATH);
		data->assets.setTexture("Asteroid 1", ASTEROID_1_FILE_PATH);
		data->assets.setTexture("Asteroid 2", ASTEROID_2_FILE_PATH);
		data->assets.setTexture("Asteroid 3", ASTEROID_3_FILE_PATH);
		data->assets.setTexture("Asteroid 4", ASTEROID_4_FILE_PATH);

		ship = new Ship(data);
	}
	void GameState::update(float dt){
		ship->physics(dt);
		this->wrap(ship->getSprite());
	}
	
	void GameState::handleInput()
	{
		sf::Event event;

		while (data->window.pollEvent(event)) {
			if (event.type == event.Closed) {
				data->window.close();
			}

		}
	}
	
	void GameState::draw(float dt) {
		data->window.clear(sf::Color::Black);
		ship->draw();
		data->window.display();
	}

	void GameState::wrap(sf::Sprite &obj) {
		sf::Vector2u windowSize = data->window.getSize();

		if (obj.getPosition().x <= 0.f - obj.getGlobalBounds().width / 2.f) {
			obj.setPosition(windowSize.x + obj.getGlobalBounds().width / 2.f, obj.getPosition().y);
		}
		else if (obj.getPosition().x >= windowSize.x + obj.getGlobalBounds().width / 2.f) {
			obj.setPosition(0.f - obj.getGlobalBounds().width / 2.f, obj.getPosition().y);
		}

		if (obj.getPosition().y <= 0.f - obj.getGlobalBounds().height / 2.f) {
			obj.setPosition(obj.getPosition().x, windowSize.y + obj.getGlobalBounds().height / 2.f);
		}
		else if (obj.getPosition().y >= windowSize.y + obj.getGlobalBounds().height / 2.f) {
			obj.setPosition(obj.getPosition().x, 0.f - obj.getGlobalBounds().height / 2.f);
		}
	}

}