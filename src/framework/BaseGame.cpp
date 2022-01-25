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

	// Limit framerate and get approximate dt
	// Limiting is inaccurate: alright for 60fps (+/- ~2fps), 120fps gets inaccurate (+/- ~10fps) and higher framerates are worse.
	// This is due to SDL working in milliseconds, so we can't do any better than 1000/17 = 111 fps or 1000/8 = 125 fps
	bool BaseGame::main_loop() {
		// Get start time
		float start_time = SDL_GetTicks();

		// 'Calculate' dt
		//float dt = WINDOW::TARGET_DT;

		// Or we could get last frame's dt - this is better
		float dt = (start_time - last_time) / 1000.0f;
		last_time = start_time;

		// Cap dt - stops game skipping time when window is dragged (which caused objects to phase through other objects)
		// Essentially makes game run slower if dt < MAX_DT
		// While window is dragged, dt accumulates because main_loop isn't called, so dt because very large
		dt = std::min(dt, WINDOW::MAX_DT);

		// Update input handler (updates all key states etc)
		input.update();

		// Handle events
		SDL_Event sdl_event;
		while (SDL_PollEvent(&sdl_event) != 0) {
			if (sdl_event.type == SDL_QUIT) {
				// X (close) is pressed
				return false;
			}
			else {
				// Delegate to InputHandler
				input.handle_sdl_event(sdl_event);
			}
		}

		update(dt);

		// Clear the screen
		/*SDLUtils::SDL_SetRenderDrawColor(renderer, COLOURS::BLACK);
		SDL_RenderClear(renderer);*/
		graphics.fill(COLOURS::BLACK);

		// Render game
		render();

		// Update screen
		SDL_RenderPresent(renderer);

		// If we were too quick, sleep!
		float end_time = SDL_GetTicks();
		float difference = end_time - start_time;
		int ticks_to_sleep = static_cast<int>(WINDOW::TARGET_DT * 1000.0f) - difference;
		if (ticks_to_sleep > 0) {
			SDL_Delay(ticks_to_sleep);
		}

		//printf("FPS: %f\n", 1.0f / dt);

		return true;
	}

	void BaseGame::update(float dt) {
		if (stage->finished()) {
			BaseStage* temp_stage = stage->next();
			delete stage;
			stage = temp_stage;
		}
		stage->update(dt, input);
	}

	void BaseGame::render() {
		stage->render(graphics);
	}

	bool BaseGame::init() {
		// Prep SDL, return false if it fails
		if (!Framework::SDLUtils::init_sdl(window, renderer)) {
			return false;
		}

		// Load game data
		load_data();

		graphics.set_renderer(renderer);

		return true;
	}

	void BaseGame::quit() {
		// Clear game data
		clear_data();
	}
}