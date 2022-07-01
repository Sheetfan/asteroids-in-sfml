#include "GameState.h"
#include "DEFINITIONS.h"
#include <iostream>

namespace buzi {
	GameState::GameState(GameDataRef data) :data(data) {}

	void GameState::init() {
		data->assets.setTexture("Ship 1", SHIP_1_FILE_PATH);
		data->assets.setTexture("Ship 2", SHIP_2_FILE_PATH);
		data->assets.setTexture("Ship 3", SHIP_3_FILE_PATH);
		data->assets.setTexture("Ship 4", SHIP_4_FILE_PATH);
		data->assets.setTexture("Asteroid 1", ASTEROID_1_FILE_PATH);
		data->assets.setTexture("Asteroid 2", ASTEROID_2_FILE_PATH);
		data->assets.setTexture("Asteroid 3", ASTEROID_3_FILE_PATH);
		data->assets.setTexture("Asteroid 4", ASTEROID_4_FILE_PATH);
		data->assets.setTexture("Asteroid 5", ASTEROID_5_FILE_PATH);
		data->assets.setTexture("Asteroid 6", ASTEROID_6_FILE_PATH);
		data->assets.setTexture("Asteroid 7", ASTEROID_7_FILE_PATH);

		ship = new Ship(data);
		asteroid = new Asteroids(data);
	}
	void GameState::update(float dt){
		std::vector <AsteroidType> &asteroids = asteroid->getAsteroids();

		ship->physics(dt);
		asteroid->physics(dt);
		this->wrap(ship->getSprite());
		this->wrap(asteroids);
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
		asteroid->draw();
		data->window.display();
	}

	void GameState::wrap(std::vector <AsteroidType> &asteroids) {
		sf::Vector2u windowSize = data->window.getSize();
		for (auto& i : asteroids) {
			if (i.asteroidsSprite.getPosition().x <= 0.f - i.asteroidsSprite.getGlobalBounds().width / 2.f) {
				i.asteroidsSprite.setPosition(windowSize.x + i.asteroidsSprite.getGlobalBounds().width / 2.f, i.asteroidsSprite.getPosition().y);
			}
			else if (i.asteroidsSprite.getPosition().x >= windowSize.x + i.asteroidsSprite.getGlobalBounds().width / 2.f) {
				i.asteroidsSprite.setPosition(0.f - i.asteroidsSprite.getGlobalBounds().width / 2.f, i.asteroidsSprite.getPosition().y);
			}

			if (i.asteroidsSprite.getPosition().y <= 0.f - i.asteroidsSprite.getGlobalBounds().height / 2.f) {
				i.asteroidsSprite.setPosition(i.asteroidsSprite.getPosition().x, windowSize.y + i.asteroidsSprite.getGlobalBounds().height / 2.f);
			}
			else if (i.asteroidsSprite.getPosition().y >= windowSize.y + i.asteroidsSprite.getGlobalBounds().height / 2.f) {
				i.asteroidsSprite.setPosition(i.asteroidsSprite.getPosition().x, 0.f - i.asteroidsSprite.getGlobalBounds().height / 2.f);
			}
		}
		
	}

	void GameState::wrap(sf::Sprite& obj) {
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