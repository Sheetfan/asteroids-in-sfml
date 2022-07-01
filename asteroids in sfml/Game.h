#pragma once

#include <memory>
#include <string>
#include <SFML/Graphics.hpp>
#include "InputManager.h"
#include "StateMachine.h"
#include "AssetManager.h"

namespace buzi {

	struct GameData {
		StateMachine machine;
		AssetManager assets;
		InputManager input;
		sf::RenderWindow window;
	};
	float angletorii(float angle);

	float sixtyFPSMove(float pixels);

	typedef std::shared_ptr<GameData> GameDataRef;

	class Game {
	private:
		// Updates run at 60 per second.
		const float dt = 1.0f / 60.0f;
		sf::Clock clock;

		GameDataRef data = std::make_shared<GameData>();

	public:
		Game(int width, int height, std::string title);
		void run();
		//changes the angle to rii to use in the trig functions
		
	};
}
