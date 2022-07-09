#include "Collision.h"

namespace buzi {
	bool Collision::boxCollision(sf::Sprite sprite, AsteroidType asteroidType){
		if (sprite.getGlobalBounds().intersects(asteroidType.asteroidsSprite.getGlobalBounds())) {
			return true;
		}
		else {
			return false;
		}
	}
	bool Collision::boxCollision(sf::Sprite sprite, std::vector<AsteroidType> asteroidTypes)
	{
		for (auto &i : asteroidTypes) {
			if (sprite.getGlobalBounds().intersects(i.asteroidsSprite.getGlobalBounds())) {
				return true;
			}
			else {
				return false;
			}
		}
		
	}
	bool Collision::boxCollision(Bullet bullet, AsteroidType asteroidType){
		if (asteroidType.asteroidsSprite.getGlobalBounds().intersects(bullet.bulletShape.
			getGlobalBounds())){
			return true;
		}
		else {
			return false;
		}
	}
}