#include "Ship.h"

buzi::Ship::Ship() {

}

void buzi::Ship::movement(float dt) {
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !(velocity >= maxVelocity)) {
		velocityDir += sf::Vector2f(dt * thrast * -cos(angletorii(angle - 90)), dt * thrast * -sin(angletorii(angle + 90)));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		angle += dt * turnRate;
		this->rotate(dt * -turnRate);

	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		angle -= dt * turnRate;
		this->rotate(dt * turnRate);
		
	}
	//velocity = sqrt(pow(velocityDir.x, 2) + pow(velocityDir.y, 2));
}

void buzi::Ship::friction(float dt) {
	

	if (velocityDir.x > dt * frictionValue) {
		velocityDir.x -= dt * frictionValue;
	}
	else if (velocityDir.x < -frictionValue * dt) {
		velocityDir.x += dt * frictionValue;
	}
	else if (velocityDir.x <= dt * frictionValue && velocityDir.x >= -frictionValue * dt) {
		velocityDir.x = 0.0;
	}

	if (velocityDir.y > dt * frictionValue) {
		velocityDir.y -= dt * frictionValue;
	}
	else if (velocityDir.y < -frictionValue * dt) {
		velocityDir.y += dt * frictionValue;
	}
	else if (velocityDir.y <= dt * frictionValue && velocityDir.y >= -frictionValue * dt) {
		velocityDir.y = 0.0;

	}
	velocity = sqrt(pow(velocityDir.x, 2) + pow(velocityDir.y, 2));
}

void buzi::Ship::physics(float dt) {
	this->movement(dt);
	this->friction(dt);
	this->move(velocityDir);
}

void buzi::Ship::setObj(sf::Texture& texture, sf::Vector2f windowSize) {
	if (!texture.loadFromFile("Sprites/ship.png")) {
		throw "ship texture not found!";
	}
	else {
		this->setTexture(texture);
		
		this->angle = 0;
		this->setRotation(0);
		this->setOrigin(this->getGlobalBounds().width / 2.f, this->getGlobalBounds().height / 2.f);
		this->setPosition(windowSize.x / 2.f, windowSize.y / 2.f);
		this->setScale(0.5f, 0.5f);
	}
}