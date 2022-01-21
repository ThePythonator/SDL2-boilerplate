#pragma once

#include "Keys.hpp"
#include "Mouse.hpp"

namespace Framework {
	class InputHandler {
	public:
		InputHandler();

		void update();

		void handle_sdl_event(const SDL_Event& sdl_event);

		void set_key(KeyHandler::Key key, KeyHandler::KeyState key_state);

		KeyHandler::KeyUnion get_key_union();

	private:
		KeyHandler::KeyUnion key_data;

		//MouseHandler::something mouse_data;
	};
}