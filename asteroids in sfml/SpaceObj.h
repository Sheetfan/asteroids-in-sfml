#pragma once

#include "SFML/Audio.hpp"
#include "SFML/Graphics.hpp"
#include <iostream>
#include <cmath>

namespace buzi {
	class SpaceObj{

protected:

	sf::Vector2f velocityDir; //the speed and direction of the space object
	float angle; //the current angle

	//how each derived class object will move
	virtual void physics(float dt) = 0;

	//changes the angle to rii to use in the trig functions
	float angletorii(float angle);

	float sixtyFPSMove(float pixels);

	virtual void setObj() = 0;

	};
}


