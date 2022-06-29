#pragma once
#include "SFML/Graphics.hpp"
#include "SpaceObj.h"
#include "Game.h"

namespace buzi {
	class Ship :public SpaceObj {
		GameDataRef data;

		sf::Sprite shipSprite;
		sf::Vector2f const shipSize = sf::Vector2f(50.f, 100.f);
		float thrast = sixtyFPSMove(2.2f);
		float frictionValue = sixtyFPSMove(0.5f);
		float turnRate = sixtyFPSMove(60.f);//How fast the ship turns
		float maxVelocity = 10.0f;
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


