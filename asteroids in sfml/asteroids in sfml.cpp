#include "Game.h"
#include "DEFINITIONS.h"

int main(){
	buzi::Game game(WINDOW_WIDTH, WINDOW_HEIGHT, "asteroids");
	game.run();
}

