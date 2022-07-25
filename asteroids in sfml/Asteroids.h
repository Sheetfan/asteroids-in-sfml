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
		float gameSpeed;
	public:
		Asteroids(GameDataRef data,float gameSpeed);

		void setObj();
		void physics(float dt);
		void draw();

		void spawnAsteroid(AsteroidType asteroid);
		void changeSpeed(float changeInSpeed);
		void restart();

		std::vector <AsteroidType> &getAsteroids();
	private:

		void randomAsteroids(int level, int howMany);
		void randomAsteroids(int level, int howMany, AsteroidType asteroidInstent);
		
	};

}

