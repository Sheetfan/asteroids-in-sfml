#pragma once

#include "SFML/Graphics.hpp"
#include "Ship.h"
#include "Asteroids.h"

namespace buzi {
	class Collision {

	public:
		Collision() {}
		bool boxCollision(sf::Sprite sprite, AsteroidType asteroidType );
		bool boxCollision(Bullet bullet, AsteroidType asteroidType);
	};
}