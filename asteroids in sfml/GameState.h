#pragma once

#include "SFML/Graphics.hpp"
#include "State.h"
#include "Game.h"
#include "Ship.h"
#include "Asteroids.h"
#include "Collision.h"
#include <vector>

namespace buzi {
	class GameState : public State {
		GameDataRef data;

		Ship *ship;
		Asteroids* asteroid;
		Collision collision;

	public:

		GameState(GameDataRef data);
	
		void init();
		void update(float dt);
		void handleInput();
		void draw(float dt);
		
		void pause() {};
		void resume() {};

		void wrap(sf::Sprite &obj);
		void wrap(std::vector <AsteroidType> &asteroids);
		void wrap(std::vector <Bullet>& bullet);

		void collisionShipAsteroid(sf::Sprite sprite, AsteroidType asteroidType);
		void collisionBulletAsteroid(Bullet bullet, AsteroidType asteroidType);
		
	};
}


