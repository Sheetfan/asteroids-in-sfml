#pragma once
#include "SFML/Graphics.hpp"
#include "Game.h"
#include <vector>

namespace buzi {
	class HUD{
		GameDataRef data;
		std::vector <sf::Sprite> lives;
		sf::Text scoreText;
		
	public:
		HUD(GameDataRef data,int lives);

		void updateLives(int lives);
		void updateScore(int score);
		void draw();

	};
}


