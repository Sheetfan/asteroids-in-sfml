#include "Game.h"
#include "GameState.h"

#include <iostream>

namespace buzi {

	Game::Game(int width, int height, std::string title) {
		data->window.create(sf::VideoMode(width, height), title, sf::Style::Close | sf::Style::Titlebar);
		data->machine.addState(StateRef(new GameState(this->data)));
	}

	void Game::run() {
		float newTime, frameTime, interpolation;

		float currentTime = this->clock.getElapsedTime().asSeconds();
		float accumulator = 0.0f;

		while (this->data->window.isOpen()) {
			this->data->machine.processStateChanges();

			newTime = this->clock.getElapsedTime().asSeconds();
			frameTime = newTime - currentTime;

			if (frameTime > 0.25f) {
				frameTime = 0.25f;
			}

			currentTime = newTime;
			accumulator += frameTime;

			while (accumulator >= dt) {

				this->data->machine.getActiveState()->handleInput();
				this->data->machine.getActiveState()->update(dt);

				accumulator -= dt;
			}

			interpolation = accumulator / dt;
			this->data->machine.getActiveState()->draw(interpolation);
		}
	}

	float angletorii(float angle) {
		return angle * 3.14159265359 / 180;
	}

	float sixtyFPSMove(float pixels) {
		return pixels / 0.17;
	}

}