#include "Mouse.hpp"

namespace Framework {
	namespace MouseHandler {
		Mouse::Mouse() {
			_buttons.buttons = { ButtonState::STILL_UP };
		}

		vec2 Mouse::position() {
			return _position;
		}

		ButtonState Mouse::button_state(MouseButton button) {
			return _buttons.button_array[static_cast<int>(button)];
		}

		void Mouse::update() {
			for (uint8_t i = 0; i < BUTTON_COUNT; i++) {
				if (_buttons.button_array[i] == ButtonState::JUST_PRESSED) {
					_buttons.button_array[i] = ButtonState::STILL_DOWN;
				}
				else if (_buttons.button_array[i] == ButtonState::JUST_RELEASED) {
					_buttons.button_array[i] = ButtonState::STILL_UP;
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
				ButtonState value = sdl_event.type == SDL_MOUSEBUTTONDOWN ? ButtonState::JUST_PRESSED : ButtonState::JUST_RELEASED;

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
	}
}