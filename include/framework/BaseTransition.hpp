#pragma once

#include "Graphics.hpp"
#include "Timer.hpp"

namespace Framework {
	class BaseTransition {
	public:
		enum class TransitionState {
			OPENING,
			OPEN,
			CLOSING,
			CLOSED
		};

		BaseTransition();

		virtual void update(float dt) = 0;
		virtual void render(Graphics* graphics) = 0;

		// Return the percentage completion of the current transition (from 0 to 1)
		virtual float percent() = 0;

		void open();
		void close();

		bool is_open();
		bool is_closed();

		TransitionState state();


	protected:
		TransitionState _state = TransitionState::OPEN;
		Timer _timer;
	};
}