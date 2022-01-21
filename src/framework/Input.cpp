#include "Input.hpp"

namespace Framework {
	InputHandler::InputHandler() {
		key_data.keys = { KeyHandler::KeyState::STILL_UP };
	}

	void InputHandler::update() {
		KeyHandler::update(key_data);
	}

	void InputHandler::handle_sdl_event(const SDL_Event& sdl_event) {
		if (sdl_event.type == SDL_KEYDOWN || sdl_event.type == SDL_KEYUP) {
			KeyHandler::update_key(key_data, sdl_event);
		}
	}

	void InputHandler::set_key(KeyHandler::Key key, KeyHandler::KeyState key_state) {
		KeyHandler::set_key(key_data, key, key_state);
	}

	KeyHandler::KeyUnion InputHandler::get_key_union() {
		return key_data;
	}
}