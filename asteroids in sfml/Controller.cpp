#include "Controller.h"
#include <SFML/Window/Joystick.hpp>

namespace buzi {
	//Controller::Controller(){}
	Controller::Controller(unsigned int controllerId , unsigned int triggerThrehold,
		unsigned int stickThrehold):controllerId(controllerId) , triggerThrehold(triggerThrehold), stickThrehold(stickThrehold) {
	}

	bool Controller::isConnected(){
		if (controllerId > 8 || controllerId < 0) {
			return false;
		}
		else {
			return sf::Joystick::isConnected(controllerId);
		}
	}

	bool Controller::A(){
		return sf::Joystick::isButtonPressed(controllerId,0);
	}

	bool Controller::B(){
		return sf::Joystick::isButtonPressed(controllerId, 1);
	}

	bool Controller::X(){
		return sf::Joystick::isButtonPressed(controllerId, 2);
	}

	bool Controller::Y(){
		return sf::Joystick::isButtonPressed(controllerId, 3);
	}

	bool Controller::RB(){
		return sf::Joystick::isButtonPressed(controllerId, 5);
	}

	bool Controller::LB(){
		return sf::Joystick::isButtonPressed(controllerId, 4);
	}

	bool Controller::RT(){
		return triggerAxises() < - triggerThrehold;
	}

	bool Controller::LT(){
		return triggerAxises() > triggerThrehold;
	}

	float Controller::triggerAxises(){
		return sf::Joystick::getAxisPosition(controllerId,sf::Joystick::Z);
	}

	bool Controller::start(){
		return sf::Joystick::isButtonPressed(controllerId, 7);
	}

	bool Controller::back(){
		return sf::Joystick::isButtonPressed(controllerId, 6);
	}

	bool Controller::R3(){
		return sf::Joystick::isButtonPressed(controllerId, 9);
	}

	bool Controller::L3(){
		return sf::Joystick::isButtonPressed(controllerId, 8);
	}

	sf::Vector2f Controller::leftStick(){
		return sf::Vector2f(sf::Joystick::getAxisPosition(controllerId, sf::Joystick::X), 
			sf::Joystick::getAxisPosition(controllerId, sf::Joystick::Y));
	}

	sf::Vector2f Controller::rightStrick(){
		return sf::Vector2f(sf::Joystick::getAxisPosition(controllerId, sf::Joystick::U),
			sf::Joystick::getAxisPosition(controllerId, sf::Joystick::R));
	}

	sf::Vector2f Controller::DPad(){
		return sf::Vector2f(sf::Joystick::getAxisPosition(controllerId, sf::Joystick::PovX), 
			- sf::Joystick::getAxisPosition(controllerId, sf::Joystick::PovY));
	}

	bool Controller::left(){
		return  DPad().x < -stickThrehold || leftStick().x < -stickThrehold;
	}

	bool Controller::right(){
		return DPad().x > stickThrehold || leftStick().x > stickThrehold;
	}

	bool Controller::up(){
		return DPad().y < -stickThrehold || leftStick().y < -stickThrehold;
	}

	bool Controller::down(){
		return DPad().y > stickThrehold || leftStick().y > stickThrehold;
	}

	//void Controller::setControllerId(unsigned int id){

	//}

	void Controller::setTriggerThrehold(float triggerThrehold){
		this->triggerThrehold = triggerThrehold;
	}

	void Controller::setStickThrehold(float stickThrehold){
		this->stickThrehold = stickThrehold;
	}

	unsigned int Controller::getControllerId(){
		return controllerId;
	}

	int Controller::getTriggerThrehold(){
		return triggerThrehold;
	}

	int Controller::getStickThrehold(){
		return stickThrehold;
	}
}
