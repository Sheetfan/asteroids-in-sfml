#pragma once
#include "SFML/Graphics.hpp"
#include "Game.h"
#include <vector>

namespace buzi {
	class HUD{
		GameDataRef data;
		std::vector <sf::Sprite> lives;
		sf::Text scoreText;
		sf::Text levelText;
		
	public:
		HUD(GameDataRef data,int lives);

		void updateLives(int lives);
		void updateScore(int score);
		void updateLevel(int level);
		void draw();

	};
}


