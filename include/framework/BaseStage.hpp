#pragma once

#include "Graphics.hpp"
#include "Input.hpp"

namespace Framework {
	class BaseStage {
	public:
		BaseStage();

		virtual void update(float dt, InputHandler& input) = 0;
		virtual void render(Graphics& graphics) = 0;

		BaseStage* next();

		bool finished();

	protected:
		void finish(BaseStage* next);

	private:
		bool _finished = false;
		BaseStage* _next = nullptr;
	};
}