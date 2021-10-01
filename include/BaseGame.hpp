#pragma once

#include "SDL.h"

#ifdef TARGET_32BLIT_HW
#include "32BlitExtras.hpp"
#else
#include "SDL2Extras.hpp"
#endif

#include "BaseStage.hpp"

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
		//virtual void update(float dt) = 0;
		//virtual void render() = 0;

		// Allows game to modify data being loaded and deleted.
		// Possibly should not be pure
		virtual void load_data() = 0;
		virtual void clear_data() = 0;

		// Current stage
		BaseStage* stage = nullptr;

	private:
		// Returns true if successful, false if something went wrong.
		bool init();
		void quit();

		// Main game loop
		bool main_loop();

		// Update and render functions
		// Not sure if should be overridable or not?
		void update(float dt);
		void render();


		// Maybe put inside some graphics wrapper?
		// Main game window
		SDL_Window* window = nullptr;

		// Renderer for window.
		SDL_Renderer* renderer = nullptr;
	};
}