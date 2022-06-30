#pragma once
#include "SFML/Graphics.hpp"
#include "SpaceObj.h"
#include "Game.h"
#include "DEFINITIONS.h"

namespace buzi {
	class Ship :public SpaceObj {
		GameDataRef data;

		sf::Sprite shipSprite;
		sf::Vector2f const shipSize = sf::Vector2f(50.f, 100.f);
		float thrast = sixtyFPSMove(SHIP_THRAST);
		float frictionValue = sixtyFPSMove(SHIP_FRICTIONVALUE);
		float turnRate = sixtyFPSMove(SHIP_TURNRATE);//How fast the ship turns
		float maxVelocity = SHIP_MAXVELOCITY;
		float velocity = 0.0f;

	public:
		Ship(GameDataRef data);
		//moves the ship according to the keys
		void movement(float dt);

		//applys friction to the ship
		void friction(float dt);

		//how each derived class object will move
		void physics(float dt);

		void draw();

		void setObj();

		sf::Sprite& getSprite();
	};
}


