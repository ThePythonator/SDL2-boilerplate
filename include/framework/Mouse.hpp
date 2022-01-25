#pragma once

#include "SDL.h"

#include "Maths.hpp"

namespace Framework {
	namespace MouseHandler {
		enum class ButtonState {
			STILL_UP, // Button isn't pressed (has already been up for at least one frame)
			JUST_RELEASED, // Button has just been released
			STILL_DOWN, // Button is pressed (has already been down for at least one frame)
			JUST_PRESSED // Button has been pressed that frame
		};

		enum class MouseButton {
			LEFT,
			MIDDLE,
			RIGHT
		};

		struct MouseButtons {
			ButtonState LEFT, MIDDLE, RIGHT;
		};

		const uint8_t BUTTON_COUNT = sizeof(MouseButtons) / sizeof(ButtonState);

		union MouseButtonUnion {
			MouseButtons buttons;
			ButtonState button_array[BUTTON_COUNT];
		};

		class Mouse {
		public:
			Mouse();

			vec2 position();
			ButtonState button_state(MouseButton button);

			void update();
			void update_mouse(const SDL_Event& sdl_event);

		private:
			vec2 _position;
			MouseButtonUnion _buttons;
		};
	}
}