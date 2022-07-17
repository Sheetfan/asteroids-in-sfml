#pragma once

#include <SFML/System/Vector2.hpp>

namespace buzi {
	class Controller {
		unsigned int controllerId;
		float triggerThrehold;
		float stickThrehold;
		
		//sf::Vector2f rightStickAixs
	public:
		//Controller();

		Controller(unsigned int controllerId, unsigned int triggerThrehold = 50,
			unsigned int stickThrehold = 50);

		bool isConnected();

		bool A();
		bool B();
		bool X();
		bool Y();

		bool RB();
		bool LB();
		bool RT();
		bool LT();

		float triggerAxises();

		bool start();
		bool back();
		
		bool R3();
		bool L3();

		sf::Vector2f leftStick();
		sf::Vector2f rightStrick();

		sf::Vector2f DPad();

		bool left();
		bool right();
		bool up();
		bool down();

		void setControllerId(unsigned int id);
		void setTriggerThrehold(float triggerThrehold);
		void setStickThrehold(float stickThrehold);

		unsigned int getControllerId();

		int getTriggerThrehold();
		int getStickThrehold();

	};
}

