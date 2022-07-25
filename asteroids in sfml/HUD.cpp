#include "HUD.h"
#include <iomanip>
#include <sstream>
#include <cmath>
namespace buzi {
	HUD::HUD(GameDataRef data,int lives):data(data) {
		std::stringstream ss;
		for (int i = 0; i < lives; i++) {
			sf::Sprite sprite;
			sprite.setTexture(data->assets.getTexture("Ship 4"));
			sprite.setPosition(60.f + sprite.getGlobalBounds().width * i, 40.f);
			sprite.setScale(0.7, 0.7);
			this->lives.push_back(sprite);
		}
		ss << std::setfill('0') << std::setw(10) << "0";
		scoreText.setFont(data->assets.getFont("Score font"));
		scoreText.setString(ss.str());
		scoreText.setCharacterSize(45);
		scoreText.setPosition(data->window.getSize().x - scoreText.getGlobalBounds().width -100.f
			, 40.f);

		levelText.setFont(data->assets.getFont("Level font"));
		levelText.setString("Level: 1");
		levelText.setCharacterSize(45);
		levelText.setPosition(data->window.getSize().y * 5/100,
			data->window.getSize().y - (levelText.getGlobalBounds().height)*3.f);
	}
	void HUD::updateLives(int lives){
		this->lives.clear();
		for (int i = 0; i < lives; i++) {
			sf::Sprite sprite;
			sprite.setTexture(data->assets.getTexture("Ship 4"));
			sprite.setPosition(60.f + sprite.getGlobalBounds().width * i, 40.f);
			sprite.setScale(0.7, 0.7);
			this->lives.push_back(sprite);
		}
	}
	void HUD::updateScore(int score){
		std::stringstream ss;

		ss << std::setfill('0') << std::setw(10) << score;
		//scoreText.setFont(data->assets.getFont("Score font"));
		scoreText.setString(ss.str());
		//scoreText.setCharacterSize(45);
		scoreText.setPosition(data->window.getSize().x - scoreText.getGlobalBounds().width - 100.f
			, 40.f);
	}
	void HUD::updateLevel(int level){
		std::stringstream ss;
		ss << "level: " << level;
		levelText.setString(ss.str());
	}
	void HUD::draw(){
		for (auto &i : lives) {
			data->window.draw(i);
		}
		data->window.draw(scoreText);
		data->window.draw(levelText);
	}
}