#pragma once
#include <memory>
#include <stack>

#include "State.h"
namespace buzi{
	typedef std::unique_ptr<State> StateRef;

	class StateMachine{
		std::stack<StateRef> states; //stores the different states
		StateRef newState; //store the new state to be added to the stack;

		bool isRemoveing; //checks if the state is being removed
		bool isAdding; //checks if the state is being added
		bool isReplacing; //checks if the state is being replaced
	public:
		StateMachine() {}
		~StateMachine() {}

		//adds a new state to the stack
		void addState(StateRef newState, bool isReplaceing = true);

		//removes the current state
		void removeState();

		//makes any changes to the state when the conditions are met
		void processStateChanges();

		StateRef& getActiveState();
	};

}

