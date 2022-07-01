#pragma once
//#include "SFML/Graphics.hpp"
#include "SpaceObj.h"
#include "Game.h"
#include "DEFINITIONS.h"
#include <array>
#include <vector>

namespace buzi {
	struct Bullet	{
		sf::CircleShape bulletShape;
		sf::Vector2f velocityVector = sf::Vector2f(0.f, 0.f);
		float velocity = sixtyFPSMove(30.f);
	};

	class Ship :public SpaceObj {
		GameDataRef data;

		sf::Sprite shipSprite;
		std::array <sf::Texture, 4> shipFrame;

		std::vector <Bullet> bullets;

		//sf::Vector2f const shipSize = sf::Vector2f(50.f, 100.f);
		float thrast = sixtyFPSMove(SHIP_THRAST);
		float frictionValue = sixtyFPSMove(SHIP_FRICTIONVALUE);
		float turnRate = sixtyFPSMove(SHIP_TURNRATE);//How fast the ship turns
		float maxVelocity = SHIP_MAXVELOCITY;
		
		float velocity = 0.0f;
		sf::Vector2f norm;

		int frame = 0;

		sf::Clock clock;
		sf::Clock clockBullet;
	public:
		Ship(GameDataRef data);
		//moves the ship according to the keys
		void movement(float dt);

		//applys friction to the ship
		void friction(float dt);

		void animate();

		//how each derived class object will move
		void physics(float dt);
		void draw();

		void setObj();

		void shoot(float dt);

		sf::Sprite& getSprite();

		std::vector <Bullet>& getBullets();
	};
}


