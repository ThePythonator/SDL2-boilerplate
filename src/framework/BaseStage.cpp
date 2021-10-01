#include "BaseStage.hpp"

namespace Framework {
	BaseStage::BaseStage() {

	}

	BaseStage* BaseStage::next() {
		return _next;
	}

	bool BaseStage::finished() {
		return _finished;
	}

	void BaseStage::finish(BaseStage* next) {
		_finished = true;
		_next = next;
	}
}