#include "Ship.h"


buzi::Ship::Ship(std::shared_ptr<GameData> data):  data(data) {
	this->setObj();
}

void buzi::Ship::movement(float dt) {
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !(velocity >= maxVelocity)) {
		velocityVector += sf::Vector2f(-cos(angletorii(angle - 90)),  -sin(angletorii(angle + 90)))* dt * thrast;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		angle += dt * turnRate;
		shipSprite.rotate(dt * -turnRate);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		angle -= dt * turnRate;
		shipSprite.rotate(dt * turnRate);
	}
	//velocity = sqrt(pow(velocityDir.x, 2) + pow(velocityDir.y, 2));
}

void buzi::Ship::friction(float dt) {
	

	if (velocityVector.x > dt * frictionValue) {
		velocityVector.x -= dt * frictionValue;
	}
	else if (velocityVector.x < -frictionValue * dt) {
		velocityVector.x += dt * frictionValue;
	}
	else if (velocityVector.x <= dt * frictionValue && velocityVector.x >= -frictionValue * dt) {
		velocityVector.x = 0.0;
	}

	if (velocityVector.y > dt * frictionValue) {
		velocityVector.y -= dt * frictionValue;
	}
	else if (velocityVector.y < -frictionValue * dt) {
		velocityVector.y += dt * frictionValue;
	}
	else if (velocityVector.y <= dt * frictionValue && velocityVector.y >= -frictionValue * dt) {
		velocityVector.y = 0.0;
	}
	velocity = sqrt(pow(velocityVector.x, 2) + pow(velocityVector.y, 2));
}

void buzi::Ship::animate(){
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		if (clock.getElapsedTime().asSeconds() > SHIP_ANIMATION_DURATION / shipFrame.size()) {
			if (frame < shipFrame.size() - 1) {
				frame++;
			}
			else {
				frame = 0;
			}
			shipSprite.setTexture(shipFrame[frame]);
			clock.restart();
		}
	}
	else {
		frame = 0;
		shipSprite.setTexture(shipFrame[frame]);
	}
}

void buzi::Ship::physics(float dt) {
	this->movement(dt);
	this->friction(dt);
	this->animate();
	this->shipSprite.move(velocityVector);
}

void buzi::Ship::draw(){
	data->window.draw(shipSprite);
}

void buzi::Ship::setObj() {
	this->angle = 0;
	this->velocityVector = sf::Vector2f(0.0,0.0);
	sf::Vector2u windowSize = data->window.getSize();
	
	shipFrame[0] = data->assets.getTexture("Ship 1");	
	shipFrame[1] = data->assets.getTexture("Ship 2");
	shipFrame[2] = data->assets.getTexture("Ship 3");
	shipFrame[3] = data->assets.getTexture("Ship 4");
	shipSprite.setTexture(shipFrame[frame]);
	shipSprite.setRotation(angle);
	shipSprite.setOrigin(shipSprite.getGlobalBounds().width / 2.f, shipSprite.getGlobalBounds().height / 2.f);
	shipSprite.setPosition(windowSize.x / 2.f, windowSize.y / 2.f);
	shipSprite.setScale(0.5f, 0.5f);
}

sf::Sprite& buzi::Ship::getSprite(){
	return shipSprite;
}
