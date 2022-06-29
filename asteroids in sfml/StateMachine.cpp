#include "StateMachine.h"

namespace buzi {
	void StateMachine::addState(StateRef newState, bool isReplaceing) {
		this->isAdding = true;
		this->isReplacing = isReplacing;
		this->newState = std::move(newState);
	}

	void StateMachine::removeState() {
		this->isRemoveing = true;
	}

	void StateMachine::processStateChanges() {

		/* if the machine is trying to remove the stack and the stack is not emply
		remove the stack*/
		if (this->isRemoveing && !this->states.empty()) {
			this->states.pop();
			if (!this->states.empty()) {
				this->states.top()->resume();
			}
			this->isReplacing = false;
		}
		if (this->isAdding) {
			if (!this->states.empty()) {
				if (this->isReplacing) {
					this->states.pop();
				}
				else {
					this->states.top()->pause();
				}
			}
			this->states.push(std::move(this->newState));
			this->states.top()->init();
			this->isAdding = false;
		}
	}

	StateRef& StateMachine::getActiveState() {
		return this->states.top();
	}
}