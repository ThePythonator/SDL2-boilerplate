#include "BaseGame.hpp"

namespace Framework {
	BaseGame::BaseGame() {

	}

	bool BaseGame::run() {
		// Initialise SDL and globals - if it fails, don't run program
		if (!init()) {
			return false;
		}

		// Allow game to get ready
		start();

		// Main game loop
		bool running = true;
		while (running) {
			running = main_loop();
		}
		
		// Allow game to clean up
		end();

		// Quit everything
		quit();

		return true;
	}

	bool BaseGame::init() {
		// Prep SDL, return false if it fails
		if (!Framework::SDL2Extras::init_sdl(window, renderer)) {
			return false;
		}

		// Load game data
		load_data();

		return true;
	}

	void BaseGame::quit() {
		// Clear game data
		clear_data();
	}

	bool BaseGame::main_loop() {
		return false;
	}
}