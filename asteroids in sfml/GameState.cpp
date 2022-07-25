#include "GameState.h"
#include "DEFINITIONS.h"
#include <iostream>

namespace buzi {
	GameState::GameState(GameDataRef data) :data(data),lives(3),score(0),gameSpeed(1),level(1) {}

	void GameState::init() {
		
		this->data->assets.setTexture("Ship 1", SHIP_1_FILE_PATH);
		this->data->assets.setTexture("Ship 2", SHIP_2_FILE_PATH);
		this->data->assets.setTexture("Ship 3", SHIP_3_FILE_PATH);
		this->data->assets.setTexture("Ship 4", SHIP_4_FILE_PATH);

		this->data->assets.setTexture("Asteroid 1", ASTEROID_1_FILE_PATH);
		this->data->assets.setTexture("Asteroid 2", ASTEROID_2_FILE_PATH);
		this->data->assets.setTexture("Asteroid 3", ASTEROID_3_FILE_PATH);
		this->data->assets.setTexture("Asteroid 4", ASTEROID_4_FILE_PATH);
		this->data->assets.setTexture("Asteroid 5", ASTEROID_5_FILE_PATH);
		this->data->assets.setTexture("Asteroid 6", ASTEROID_6_FILE_PATH);
		this->data->assets.setTexture("Asteroid 7", ASTEROID_7_FILE_PATH);

		this->data->assets.setTexture("Explosion 1", EXPLOSION_1_FILE_PATH);
		this->data->assets.setTexture("Explosion 2", EXPLOSION_2_FILE_PATH);
		this->data->assets.setTexture("Explosion 3", EXPLOSION_3_FILE_PATH);
		this->data->assets.setTexture("Explosion 4", EXPLOSION_4_FILE_PATH);

		this->data->assets.setFont("Score font", HUD_SCORE_FONT);
		this->data->assets.setFont("Level font", HUD_Level_FONT);

		this->ship = new Ship(data);
		this->asteroid = new Asteroids(data,gameSpeed);
		this->hud = new HUD(data, lives);
		
		this->state = GameStates::eReady;

		this->gameText.setFont(data->assets.getFont("Score font"));
		this->gameText.setString("Ready");
		this->gameText.setCharacterSize(100);
		this->gameText.setOrigin(this->gameText.getGlobalBounds().width / 2.f, this->gameText.getGlobalBounds()
			.height / 2.f);
		this->gameText.setPosition(data->window.getSize().x / 2.f, data->window.getSize().y / 2.f);
		readyTimer.restart();
	}
	void GameState::update(float dt) {
		sf::Sprite& shipSprite = this->ship->getSprite();
		std::vector <AsteroidType>& asteroidSprites = this->asteroid->getAsteroids();
		std::vector <Bullet>& bullets = this->ship->getBullets();

		if (this->state == GameStates::eReady) {
			this->gameText.setString("Ready");
			this->gameText.setOrigin(this->gameText.getGlobalBounds().width / 2.f, this->gameText.getGlobalBounds()
				.height / 2.f);
			this->gameText.setPosition(data->window.getSize().x / 2.f, data->window.getSize().y / 2.f);
		}
		if (this->state == GameStates::eReady && readyTimer.getElapsedTime().asSeconds() > READY_STATE_DELAY) {
			this->state = GameStates::ePlaying;
		}
		if (state == GameStates::eDied) {
			this->ship->animateExplosion(state,dt);

		}

		//makes sure the timer only resets once the respawn state started 
		if (state == GameStates::eRespawn && readytimerSet == false) {
			readytimerSet = true;
			readyTimer.restart();
		}
		//after the respawn delay the ship will respawn
		if (state == GameStates::eRespawn && readyTimer.getElapsedTime().asSeconds() > 
			SHIP_RESPAWN_DELAY && !collision.boxCollision(shipSprite, asteroidSprites)) {
			this->ship->respawn();
			state = GameStates::ePlaying;
			readytimerSet = false;
		}
		// it starts the game after the eReady state
		if (state != GameStates::eReady) {
			if (state == GameStates::ePlaying) {
				this->ship->physics(dt);
			}
			this->ship->despawnBullet();
			
			this->asteroid->physics(dt);
			this->wrap(shipSprite);
			this->wrap(asteroidSprites);
			this->wrap(bullets);
			if (state == GameStates::ePlaying) {
				this->collisionShipAsteroid(shipSprite, asteroidSprites);
			}

			this->collisionBulletAsteroid(bullets, asteroidSprites);
			for (auto& i : bullets) {
				i.bulletShape.move(i.velocityVector * dt);
			}
		}
		
		if (this->state == GameStates::eRespawn && lives == 0) {
			state = GameStates::eGameOver;
		}

		//it will display game text while in the game over state
		if (state == GameStates::eGameOver) {
			gameText.setString("Game Over!!!");
			this->gameText.setOrigin(this->gameText.getGlobalBounds().width / 2.f, this->gameText.getGlobalBounds()
				.height / 2.f);
			this->gameText.setPosition(data->window.getSize().x / 2.f, data->window.getSize().y / 2.f);
		}

		//it was will go to the next level when the all asteroid are gone
		if (asteroidSprites.size() == 0 && state == GameStates::ePlaying) {
			hud->updateLevel(++level);
			gameSpeed += 0.2;
			asteroid->changeSpeed(gameSpeed);
			asteroid->setObj();
			ship->reset();
			state = GameStates::eReady;
			bullets.clear();
			readyTimer.restart();
			//readytimerSet = false;
		}
	}
	
	void GameState::handleInput(){
		sf::Event event;

		while (this->data->window.pollEvent(event)) {
			if (event.type == event.Closed) {
				this->data->window.close();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::R) && state == 
				GameStates::eGameOver) {
				restart();
			}
		}
	}
	
	void GameState::draw(float dt) {
		std::vector <Bullet>& bullets = this->ship->getBullets();
		this->data->window.clear(sf::Color::Black);
		
		if (state == GameStates::eReady || state == GameStates::eGameOver) {
			data->window.draw(this->gameText);
		}
		if (state != GameStates::eRespawn && state != GameStates::eGameOver) {
			this->ship->draw();
		}
		for (auto &i : bullets) {
			data->window.draw(i.bulletShape);
		}
		
		this->asteroid->draw();
		this->hud->draw();
		this->data->window.display();
	}

	void GameState::restart(){
		lives = 3;
		score = 0;
		hud->updateLives(lives);
		hud->updateScore(score);
		this->ship->respawn();
		asteroid->restart();
		level = 1;
		state = GameStates::eReady;
		
	}

	void GameState::wrap(sf::Sprite& obj) {
		sf::Vector2u windowSize = data->window.getSize();

		if (obj.getPosition().x <= 0.f - obj.getGlobalBounds().width / 2.f) {
			obj.setPosition(windowSize.x + obj.getGlobalBounds().width / 2.f, obj.getPosition().y);
		}
		else if (obj.getPosition().x >= windowSize.x + obj.getGlobalBounds().width / 2.f) {
			obj.setPosition(0.f - obj.getGlobalBounds().width / 2.f, obj.getPosition().y);
		}

		if (obj.getPosition().y <= 0.f - obj.getGlobalBounds().height / 2.f) {
			obj.setPosition(obj.getPosition().x, windowSize.y + obj.getGlobalBounds().height / 2.f);
		}
		else if (obj.getPosition().y >= windowSize.y + obj.getGlobalBounds().height / 2.f) {
			obj.setPosition(obj.getPosition().x, 0.f - obj.getGlobalBounds().height / 2.f);
		}
	}

	void GameState::wrap(std::vector <AsteroidType> &asteroids) {
		sf::Vector2u windowSize = data->window.getSize();
		for (auto& i : asteroids) {
			if (i.asteroidsSprite.getPosition().x <= 0.f - i.asteroidsSprite.getGlobalBounds().width / 2.f) {
				i.asteroidsSprite.setPosition(windowSize.x + i.asteroidsSprite.getGlobalBounds().width / 2.f, i.asteroidsSprite.getPosition().y);
			}
			else if (i.asteroidsSprite.getPosition().x >= windowSize.x + i.asteroidsSprite.getGlobalBounds().width / 2.f) {
				i.asteroidsSprite.setPosition(0.f - i.asteroidsSprite.getGlobalBounds().width / 2.f, i.asteroidsSprite.getPosition().y);
			}

			if (i.asteroidsSprite.getPosition().y <= 0.f - i.asteroidsSprite.getGlobalBounds().height / 2.f) {
				i.asteroidsSprite.setPosition(i.asteroidsSprite.getPosition().x, windowSize.y + i.asteroidsSprite.getGlobalBounds().height / 2.f);
			}
			else if (i.asteroidsSprite.getPosition().y >= windowSize.y + i.asteroidsSprite.getGlobalBounds().height / 2.f) {
				i.asteroidsSprite.setPosition(i.asteroidsSprite.getPosition().x, 0.f - i.asteroidsSprite.getGlobalBounds().height / 2.f);
			}
		}
		
	}

	void GameState::wrap(std::vector <Bullet>& bullet) {
		sf::Vector2u windowSize = data->window.getSize();
		for (auto& i : bullet) {
			if (i.bulletShape.getPosition().x <= 0.f - i.bulletShape.getRadius() ){
				i.bulletShape.setPosition(windowSize.x + i.bulletShape.getRadius(), i.bulletShape.getPosition().y);
			}
			else if (i.bulletShape.getPosition().x >= windowSize.x + i.bulletShape.getRadius()) {
				i.bulletShape.setPosition(0.f - i.bulletShape.getRadius(), i.bulletShape.getPosition().y);
			}

			if (i.bulletShape.getPosition().y <= 0.f - i.bulletShape.getRadius()) {
				i.bulletShape.setPosition(i.bulletShape.getPosition().x, windowSize.y + i.bulletShape.getRadius() / 2.f);
			}
			else if (i.bulletShape.getPosition().y >= windowSize.y + i.bulletShape.getRadius()) {
				i.bulletShape.setPosition(i.bulletShape.getPosition().x, 0.f - i.bulletShape.getRadius());
			}
		}

	}

	void GameState::collisionShipAsteroid(sf::Sprite &sprite, std::vector <AsteroidType>& asteroidSprites){
		for (auto i : asteroidSprites) {
			if (collision.boxCollision(sprite, i)) {
				hud->updateLives(--lives);
				this->state = GameStates::eDied;
				break;
			}
		}
		
	}

	void GameState::collisionBulletAsteroid(std::vector <Bullet>& bullet, std::vector <AsteroidType>& asteroidSprites){
		for (int i = 0; i < bullet.size(); i++) {
			for (int k = 0; k < asteroidSprites.size();k++) {
				if (collision.boxCollision(bullet[i],asteroidSprites[k])) {

					bullet.erase(bullet.begin() + i);
					this->asteroid->spawnAsteroid(asteroidSprites[k]);
					asteroidSprites.erase(asteroidSprites.begin() + k);
					this->score += 10;
					hud->updateScore(score);
					break;
				}
			}
		}
	}
}