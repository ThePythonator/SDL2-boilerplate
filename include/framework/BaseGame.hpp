#pragma once

#include <algorithm>
#include <vector>

#include "SDL.h"

#include "Constants.hpp"

#include "SDLUtils.hpp"

#include "BaseStage.hpp"
#include "Input.hpp"
#include "Graphics.hpp"

namespace Framework {
	class BaseGame {
	public:
		BaseGame();

		// Returns true if successful, false if something went wrong.
		bool run();

	protected:
		// Allows game to execute code before main loop, and after last loop.
		virtual void start() = 0;
		virtual void end() = 0;

		// Update and render functions
		/*virtual void update(float dt) = 0;
		virtual void render() = 0;*/

		// Allows game to modify data being loaded and deleted.
		// Possibly should not be pure
		virtual void load_data() = 0;
		virtual void clear_data() = 0;

		InputHandler input;
		Graphics graphics;

		// Current stage
		BaseStage* stage = nullptr;

	private:
		// Returns true if successful, false if something went wrong.
		bool init();
		void quit();

		void update(float dt);
		void render();

		// Main game loop
		bool main_loop();

		float last_time = 0.0f;

		// Main game window
		SDL_Window* window = nullptr;

		// Renderer for window
		SDL_Renderer* renderer = nullptr;
	};
}