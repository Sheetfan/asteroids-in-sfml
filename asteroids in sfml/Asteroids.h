#pragma once
//#include "SFML/Graphics.hpp"
#include "SpaceObj.h"
#include "Game.h"
#include <vector>
#include "DEFINITIONS.h"


namespace buzi {
	struct AsteroidType {
		int level;
		float angle;
		float velocity = sixtyFPSMove(ASTERIOD_VELOCITY);
		sf::Sprite asteroidsSprite;
		sf::Vector2f velocityVector;
	};
	class Asteroids :public SpaceObj{

		
		GameDataRef data;

		std::vector <AsteroidType> asteroids;

	public:
		Asteroids(GameDataRef data);
		void setObj();
		void physics(float dt);
		void draw();
		void spawnAsteroid();

		std::vector <AsteroidType> &getAsteroids();
	private:

	};

}

