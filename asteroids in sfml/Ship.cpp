#include "Ship.h"
#include <iostream>


namespace buzi {
	Ship::Ship(std::shared_ptr<GameData> data) : data(data) {
		this->setObj();
	}

	void Ship::setObj() {
		this->angle = 0;
		this->velocityVector = sf::Vector2f(0.0, 0.0);

		norm = sf::Vector2f(0.f, -1.f);

		sf::Vector2u windowSize = data->window.getSize();

		shipTexture[0] = &data->assets.getTexture("Ship 1");
		shipTexture[1] = &data->assets.getTexture("Ship 2");
		shipTexture[2] = &data->assets.getTexture("Ship 3");
		shipTexture[3] = &data->assets.getTexture("Ship 4");

		explosionFrame[0] = &data->assets.getTexture("Explosion 1");
		explosionFrame[1] = &data->assets.getTexture("Explosion 2");
		explosionFrame[2] = &data->assets.getTexture("Explosion 3");
		explosionFrame[3] = &data->assets.getTexture("Explosion 4");

		shipSprite.setTexture(*shipTexture[frame]);
		//shipSprite.setTexture(*explosionFrame[frame]);
		shipSprite.setRotation(angle);
		shipSprite.setOrigin(shipSprite.getGlobalBounds().width / 2.f, shipSprite.getGlobalBounds().height / 2.f);
		shipSprite.setPosition(windowSize.x / 2.f, windowSize.y / 2.f);
		
		shipSprite.setScale(0.5f, 0.5f);
	}

	void Ship::movement(float dt) {

		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::W) || data->input.getController().up()) && !(velocity >= maxVelocity)) {
			norm = sf::Vector2f(cos(angletorii(angle + 90)), sin(angletorii(angle - 90)));
			velocityVector += norm * dt * thrast;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || data->input.getController().left()) {
			angle += dt * turnRate;
			shipSprite.rotate(dt * -turnRate);
			norm = sf::Vector2f(cos(angletorii(angle + 90)), sin(angletorii(angle - 90)));
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || data->input.getController().right()) {
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

	void Ship::animateMovement() {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || data->input.getController().up()) {
			if (clock.getElapsedTime().asSeconds() > SHIP_ANIMATION_DURATION / shipTexture.size()) {
				if (frame < shipTexture.size() - 1) {
					frame++;
				}
				else {
					frame = 0;
				}
				shipSprite.setTexture(*shipTexture[frame]);
				clock.restart();
			}

		}
		else {
			frame = 0;
			shipSprite.setTexture(*shipTexture[frame]);
		}
	}

	void Ship::animateExplosion(GameStates &state,float dt){
		sf::Vector2u windowSize = data->window.getSize();
		if (clock.getElapsedTime().asSeconds() > EXPLOSION_ANIMATION_DURATION / explosionFrame.size()) {
			if (frameExplosion < explosionFrame.size()) {
	
				shipSprite.setTexture(*explosionFrame[frameExplosion], true);
				shipSprite.setScale(1.0f, 1.0f);
				shipSprite.setOrigin(shipSprite.getGlobalBounds().width / 2.f, shipSprite.getGlobalBounds().height
					/ 2.f);
				frameExplosion++;
			}
			else {
				//shipSprite.setTexture(*explosionFrame[frameExplosion], true);
				frameExplosion = 0;
				state = GameStates::eRespawn;
				//shipSprite.setTextureRect()
			}
			

			clock.restart();
		}
	}

	void Ship::physics(float dt) {
		this->movement(dt);
		this->friction(dt);
		this->animateMovement();
		this->shipSprite.move(velocityVector);
		this->shoot(dt);
	}

	void Ship::draw() {
		//for (auto& i : bullets) {
		//	data->window.draw(i.bulletShape);
		//}
		data->window.draw(shipSprite);
	}

	void Ship::shoot(float dt) {
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Space)||(sf::Mouse::isButtonPressed(sf::Mouse::Left))
			|| data->input.getController().A()) &&
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
	}

	void Ship::despawnBullet(){
		for (int i = 0; i < bullets.size(); i++) {
			if (bullets[i].lifeTime.getElapsedTime().asSeconds() > BULLET_DESPAWN_TIME) {
				bullets.erase(bullets.begin() + i);
			}
		}
	}

	void Ship::respawn(){
		this->angle = 0;
		this->velocityVector = sf::Vector2f(0.0, 0.0);
		frame = 0;
		norm = sf::Vector2f(0.f, -1.f);

		sf::Vector2u windowSize = data->window.getSize();

		shipSprite.setTexture(*shipTexture[frame],true);
		shipSprite.setRotation(angle);
		shipSprite.setOrigin(shipSprite.getGlobalBounds().width / 2.f, shipSprite.getGlobalBounds().height
			/ 2.f);
		shipSprite.setPosition(windowSize.x / 2.f, windowSize.y / 2.f);
		shipSprite.setScale(0.5f, 0.5f);
	}

	sf::Sprite& Ship::getSprite() {
		return shipSprite;
	}

	std::vector<Bullet>& Ship::getBullets(){
		return bullets;
	}
}
