#pragma once

#include "SFML/Graphics.hpp"
#include "Ship.h"
#include "Asteroids.h"
#include <vector>

namespace buzi {
	class Collision {

		
	public: 

		Collision() {}
		bool boxCollision(sf::Sprite sprite, AsteroidType asteroidType );
		bool boxCollision(sf::Sprite sprite,std::vector <AsteroidType> asteroidTypes);
		bool boxCollision(Bullet bullet, AsteroidType asteroidType);
	};
}