#pragma once

#include "SFML/Graphics.hpp"
#include "State.h"
#include "Game.h"
#include "Ship.h"
#include "Asteroids.h"
#include "HUD.h"
#include "Collision.h"
#include <vector>

namespace buzi {

	class GameState : public State {
		GameDataRef data;
		GameStates state;

		Ship *ship;
		Asteroids* asteroid;
		HUD* hud;

		Collision collision;

		sf::Clock readyTimer;

		bool readytimerSet;
		int lives;
		int score;
	public:

		GameState(GameDataRef data);
	
		void init();
		void update(float dt);
		void handleInput();
		void draw(float dt);
		
		void pause() {};
		void resume() {};

	private:
		void wrap(sf::Sprite& obj);
		void wrap(std::vector <AsteroidType>& asteroids);
		void wrap(std::vector <Bullet>& bullet);

		void collisionShipAsteroid(sf::Sprite& sprite, std::vector <AsteroidType>& asteroidSprites);
		void collisionBulletAsteroid(std::vector <Bullet>& bullet, std::vector <AsteroidType>& asteroidSprites);
	};
}


