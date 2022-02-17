#include "Mouse.hpp"

namespace Framework {
	namespace MouseHandler {
		Mouse::Mouse() {
			_buttons.buttons = { MouseButtonState::STILL_UP };
		}

		vec2 Mouse::position() {
			return _position;
		}

		MouseButtonState Mouse::button_state(MouseButton button) {
			return _buttons.button_array[static_cast<int>(button)];
		}

		bool Mouse::pressed(MouseButton button) {
			MouseButtonState state = button_state(button);
			return state == MouseButtonState::JUST_PRESSED || state == MouseButtonState::STILL_DOWN;
		}

		void Mouse::update() {
			for (uint8_t i = 0; i < BUTTON_COUNT; i++) {
				if (_buttons.button_array[i] == MouseButtonState::JUST_PRESSED) {
					_buttons.button_array[i] = MouseButtonState::STILL_DOWN;
				}
				else if (_buttons.button_array[i] == MouseButtonState::JUST_RELEASED) {
					_buttons.button_array[i] = MouseButtonState::STILL_UP;
				}
			}
		}

		void Mouse::update_mouse(const SDL_Event& sdl_event) {
			if (sdl_event.type == SDL_MOUSEMOTION) {
				// Update position
				_position = vec2{ static_cast<float>(sdl_event.motion.x), static_cast<float>(sdl_event.motion.y) };
			}
			else if (sdl_event.type == SDL_MOUSEBUTTONDOWN || sdl_event.type == SDL_MOUSEBUTTONUP) {
				// Is button pressed or released?
				MouseButtonState value = sdl_event.type == SDL_MOUSEBUTTONDOWN ? MouseButtonState::JUST_PRESSED : MouseButtonState::JUST_RELEASED;

				// Check which button is pressed
				switch (sdl_event.button.button) {
				case SDL_BUTTON_LEFT:
					_buttons.buttons.LEFT = value;
					break;
				case SDL_BUTTON_MIDDLE:
					_buttons.buttons.MIDDLE = value;
					break;
				case SDL_BUTTON_RIGHT:
					_buttons.buttons.RIGHT = value;
					break;
				default:
					break;
				}
			}
		}

		void Mouse::set_cursor(bool visible) {
			SDL_ShowCursor(visible ? SDL_ENABLE : SDL_DISABLE);
		}
	}
}