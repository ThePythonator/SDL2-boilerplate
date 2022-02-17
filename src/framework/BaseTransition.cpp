#include "BaseTransition.hpp"

namespace Framework {
	BaseTransition::BaseTransition() {

	}

	bool BaseTransition::is_open() {
		return _state == TransitionState::OPEN;
	}
	bool BaseTransition::is_closed() {
		return _state == TransitionState::CLOSED;
	}

	BaseTransition::TransitionState BaseTransition::state() {
		return _state;
	}

	void BaseTransition::open() {
		_state = TransitionState::OPENING;
		_timer.reset();
		_timer.start();
	}

	void BaseTransition::close() {
		_state = TransitionState::CLOSING;
		_timer.reset();
		_timer.start();
	}
}