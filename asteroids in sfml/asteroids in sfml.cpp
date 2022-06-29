#include "Game.h"
#include "DEFINITIONS.h"

sf::Vector2f windowSize = sf::Vector2f(1200.f, 1000.f);

int main(){
	buzi::Game game(WINDOW_WIDTH, WINDOW_WIDTH, "asteroids");
	game.run();
}

