#include "Ship.h"
#include <iostream>


namespace buzi {
	Ship::Ship(std::shared_ptr<GameData> data) : data(data) {
		this->setObj();
	}

	void Ship::movement(float dt) {

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !(velocity >= maxVelocity)) {
			norm = sf::Vector2f(cos(angletorii(angle + 90)), sin(angletorii(angle - 90)));
			velocityVector += norm * dt * thrast;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			angle += dt * turnRate;
			shipSprite.rotate(dt * -turnRate);
			norm = sf::Vector2f(cos(angletorii(angle + 90)), sin(angletorii(angle - 90)));
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			angle -= dt * turnRate;
			shipSprite.rotate(dt * turnRate);
			norm = sf::Vector2f(cos(angletorii(angle + 90)), sin(angletorii(angle - 90)));
		}
		//velocity = sqrt(pow(velocityDir.x, 2) + pow(velocityDir.y, 2));
	}

	void Ship::friction(float dt) {


		if (velocityVector.x > dt * frictionValue) {
			velocityVector.x -= dt * frictionValue;
		}
		else if (velocityVector.x < -frictionValue * dt) {
			velocityVector.x += dt * frictionValue;
		}
		//else if (velocityVector.x <= dt * frictionValue && velocityVector.x >= -frictionValue * dt) {
		//	velocityVector.x = 0.0;
		//}

		if (velocityVector.y > dt * frictionValue) {
			velocityVector.y -= dt * frictionValue;
		}
		else if (velocityVector.y < -frictionValue * dt) {
			velocityVector.y += dt * frictionValue;
		}
		//else if (velocityVector.y <= dt * frictionValue && velocityVector.y >= -frictionValue * dt) {
		//	velocityVector.y = 0.0;
		//}
		if (velocityVector.y <= dt * frictionValue && velocityVector.y >= -frictionValue * dt &&
			velocityVector.x <= dt * frictionValue && velocityVector.x >= -frictionValue * dt) {
			velocityVector.y = 0.0;
			velocityVector.x = 0.0;
		}
		velocity = sqrt(pow(velocityVector.x, 2) + pow(velocityVector.y, 2));
		//std::cout << velocityVector.x << "," << velocityVector.y << "\n";
	}

	void Ship::animate() {
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

	void Ship::physics(float dt) {
		this->movement(dt);
		this->friction(dt);
		this->animate();
		this->shipSprite.move(velocityVector);
		this->shoot(dt);
		for (auto &i : bullets) {
			i.bulletShape.move(i.velocityVector * dt);
		}
	}

	void Ship::draw() {
		for (auto& i : bullets) {
			data->window.draw(i.bulletShape);
		}
		data->window.draw(shipSprite);
		
	}

	void Ship::setObj() {
		this->angle = 0;
		this->velocityVector = sf::Vector2f(0.0, 0.0);

		norm = sf::Vector2f(0.f,-1.f);
		
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
	void Ship::shoot(float dt) {
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Space)||(sf::Mouse::isButtonPressed(sf::Mouse::Left))) &&
			(clockBullet.getElapsedTime().asSeconds() > 1/BULLET_RATE)) {
			Bullet bullet;
			bullet.bulletShape.setRadius(2.f);
			bullet.bulletShape.setOrigin(bullet.bulletShape.getRadius(), bullet.bulletShape.getRadius());
			
			bullet.bulletShape.setPosition(shipSprite.getPosition().x, shipSprite.getPosition().y);
			
			bullet.bulletShape.setFillColor(sf::Color::White);
			bullet.velocityVector = norm * bullet.velocity;
			bullets.push_back(bullet);
			clockBullet.restart();
		}
	};

	sf::Sprite& Ship::getSprite() {
		return shipSprite;
	}

	std::vector<Bullet>& Ship::getBullets(){
		return bullets;
	}

}
