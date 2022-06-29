#pragma once

#include "State.h"
#include "Game.h"
#include "Ship.h"
#include "SFML/Graphics.hpp"

namespace buzi {
	class GameState : public State {
		sf::Texture texture;
		Ship *ship;

		float dt = 0.0;

		GameDataRef data;
	public:

		GameState(GameDataRef data);
	
		void init();
		void update(float dt);
		void handleInput();
		void draw(float dt);
		
		void pause() {};
		void resume() {};

		void wrap(sf::Sprite &obj);

		
	};
}


