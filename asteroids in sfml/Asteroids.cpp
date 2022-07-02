#include "Asteroids.h"
#include <random>
#include <iostream>

namespace buzi {
	Asteroids::Asteroids(GameDataRef data) : data(data) {
		setObj();
	}
	void Asteroids::setObj() {
		randomAsteroids(1, 4);
		
		asteroids[0].asteroidsSprite.setPosition(data->window.getSize().x * (25.f / 100.f),
			data->window.getSize().y * (25.f / 100.f));
		asteroids[1].asteroidsSprite.setPosition(data->window.getSize().x * (75.f / 100.f),
			data->window.getSize().y * (25.f / 100.f));
		asteroids[2].asteroidsSprite.setPosition(data->window.getSize().x * (25.f / 100.f),
			data->window.getSize().y * (75.f / 100.f));
		asteroids[3].asteroidsSprite.setPosition(data->window.getSize().x * (75.f / 100.f),
			data->window.getSize().y * (75.f / 100.f));

		for (auto& i : asteroids){
			i.asteroidsSprite.setScale(0.5, 0.5);
		}
	}
	void Asteroids::physics(float dt) {
		for (auto& i : asteroids) {
			i.asteroidsSprite.move(i.velocityVector * dt);
			//i.asteroidsSprite.rotate(sixtyFPSMove(10.f) * dt);
		}
	}
	void Asteroids::draw() {
		for (auto& i : asteroids) {
			data->window.draw(i.asteroidsSprite);
		}
	}

	void Asteroids::spawnAsteroid(AsteroidType asteroid) {
		if (asteroid.level < 3 ) {
			randomAsteroids(++asteroid.level, 2, asteroid);
			
		}
	}

	void Asteroids::randomAsteroids(int level, int howMany){
		int random;

		std::random_device rd;
		std::mt19937 mt(rd());
		std::uniform_int_distribution <size_t> disRamdomTexture(0, 4);
		std::uniform_int_distribution <size_t> disRamdomAngle(0, 360);

		AsteroidType asteroid;

		for (int i = 0; i < howMany; i++) {
			random = disRamdomTexture(mt);
			switch (random) {
			case 0:
				asteroid.asteroidsSprite.setTexture(data->assets.getTexture("Asteroid 1"));
				break;
			case 1:
				asteroid.asteroidsSprite.setTexture(data->assets.getTexture("Asteroid 2"));
				break;
			case 2:
				asteroid.asteroidsSprite.setTexture(data->assets.getTexture("Asteroid 3"));
				break;
			case 3:
				asteroid.asteroidsSprite.setTexture(data->assets.getTexture("Asteroid 4"));
				break;
			case 4:
				asteroid.asteroidsSprite.setTexture(data->assets.getTexture("Asteroid 5"));
				break;
			case 5:
				asteroid.asteroidsSprite.setTexture(data->assets.getTexture("Asteroid 6"));
				break;
			case 6:
				asteroid.asteroidsSprite.setTexture(data->assets.getTexture("Asteroid 7"));
				break;
			}
			asteroid.angle = disRamdomAngle(mt);
			asteroid.level = level;
			asteroid.velocityVector = sf::Vector2f(-cos(angletorii(asteroid.angle)), sin(-angletorii(asteroid.angle))) * asteroid.velocity;

			asteroid.asteroidsSprite.setOrigin(asteroid.asteroidsSprite.getGlobalBounds().width / 2.f,
				asteroid.asteroidsSprite.getGlobalBounds().height / 2.f);
			asteroids.push_back(asteroid);

		}
	}
	void Asteroids::randomAsteroids(int level, int howMany, AsteroidType asteroidInstent){
		int random;

		std::random_device rd;
		std::mt19937 mt(rd());
		std::uniform_int_distribution <size_t> disRamdomTexture(0, 4);
		std::uniform_int_distribution <size_t> disRamdomAngle(0, 360);

		AsteroidType asteroid;
		
		for (int i = 0; i < howMany; i++) {
			random = disRamdomTexture(mt);
			switch (random) {
			case 0:
				asteroid.asteroidsSprite.setTexture(data->assets.getTexture("Asteroid 1"));
				break;
			case 1:
				asteroid.asteroidsSprite.setTexture(data->assets.getTexture("Asteroid 2"));
				break;
			case 2:
				asteroid.asteroidsSprite.setTexture(data->assets.getTexture("Asteroid 3"));
				break;
			case 3:
				asteroid.asteroidsSprite.setTexture(data->assets.getTexture("Asteroid 4"));
				break;
			case 4:
				asteroid.asteroidsSprite.setTexture(data->assets.getTexture("Asteroid 5"));
				break;
			case 5:
				asteroid.asteroidsSprite.setTexture(data->assets.getTexture("Asteroid 6"));
				break;
			case 6:
				asteroid.asteroidsSprite.setTexture(data->assets.getTexture("Asteroid 7"));
				break;
			}
			asteroid.angle = disRamdomAngle(mt);
			asteroid.level = level;
			asteroid.velocityVector = sf::Vector2f(-cos(angletorii(asteroid.angle)), sin(-angletorii(asteroid.angle))) * asteroid.velocity * ((float) level) * 1.f;

			asteroid.asteroidsSprite.setOrigin(asteroid.asteroidsSprite.getGlobalBounds().width / 2.f,
				asteroid.asteroidsSprite.getGlobalBounds().height / 2.f);
			asteroid.asteroidsSprite.setPosition(asteroidInstent.asteroidsSprite.getPosition().x,
				asteroidInstent.asteroidsSprite.getPosition().y);
			asteroid.asteroidsSprite.setScale(asteroidInstent.asteroidsSprite.getScale().x *
				0.3, asteroidInstent.asteroidsSprite.getScale().y* 0.4);
			asteroids.push_back(asteroid);

		}
		
	}
	
	std::vector<AsteroidType>& Asteroids::getAsteroids() {
		return asteroids;
	}
}