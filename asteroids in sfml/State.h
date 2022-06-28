#pragma once

namespace buzi {
	class State {
		State() {}

		virtual void init() = 0;
		virtual void update() = 0;
		virtual void draw() = 0;

		virtual void pause() {};
		virtual void resume() {};
	};

}

