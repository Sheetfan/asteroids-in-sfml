#pragma once

#include "SFML/Audio.hpp"
#include "SFML/Graphics.hpp"
#include <iostream>
#include <cmath>

namespace buzi {
	class SpaceObj{

protected:

	sf::Vector2f velocityVector; //the speed and direction of the space object
	float angle; //the current angle

	//how each derived class object will move
	virtual void physics(float dt) = 0;

	virtual void draw() = 0;

	virtual void setObj() = 0;

	};
}


