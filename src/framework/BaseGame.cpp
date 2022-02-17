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
		// Game must set stage ptr
		start();
		stage->init(&graphics_objects, &input);

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
		uint32_t start_time = SDL_GetTicks();

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

		bool running = update(dt);

		// Clear the screen
		/*SDLUtils::SDL_SetRenderDrawColor(renderer, COLOURS::BLACK);
		SDL_RenderClear(renderer);*/
		graphics_objects.graphics_ptr->fill(COLOURS::BLACK);

		// Render game
		render();

		// Update screen
		SDL_RenderPresent(renderer);

		// If we were too quick, sleep!
		uint32_t end_time = SDL_GetTicks();
		uint32_t difference = end_time - start_time;
		int ticks_to_sleep = static_cast<int>(WINDOW::TARGET_DT * 1000.0f) - difference;
		if (ticks_to_sleep > 0) {
			SDL_Delay(ticks_to_sleep);
		}

		//printf("FPS: %f\n", 1.0f / dt);

		return running;
	}

	bool BaseGame::update(float dt) {
		if (stage->finished()) {
			// Allow user to clear up anything
			stage->end();

			if (stage->delete_me()) {
				BaseStage* temp_stage = stage->next();
				delete stage;
				stage = temp_stage;
			}
			else {
				stage = stage->next();
			}
			
			// Setup next stage
			stage->init(&graphics_objects, &input);
		}

		bool running = stage->update(dt);
		return running;
	}

	void BaseGame::render() {
		stage->render();
	}

	bool BaseGame::init() {
		// Prep SDL, return false if it fails
		if (!Framework::SDLUtils::init_sdl(window, renderer)) {
			return false;
		}

		graphics_objects.graphics_ptr = new Graphics();
		graphics_objects.graphics_ptr->set_renderer(renderer);

		// Set up graphics_objects vectors:
		graphics_objects.image_ptrs = std::vector<Framework::Image*>(GRAPHICS_OBJECTS::IMAGES::TOTAL_IMAGES);
		graphics_objects.spritesheet_ptrs = std::vector<Framework::Spritesheet*>(GRAPHICS_OBJECTS::SPRITESHEETS::TOTAL_SPRITESHEETS);
		graphics_objects.font_ptrs = std::vector<Framework::Font*>(GRAPHICS_OBJECTS::FONTS::TOTAL_FONTS);
		graphics_objects.transition_ptrs = std::vector<Framework::BaseTransition*>(GRAPHICS_OBJECTS::TRANSITIONS::TOTAL_TRANSITIONS);

		// Load game data
		load_data();

		return true;
	}

	void BaseGame::quit() {
		// Clear game data
		clear_data();

		// Clear graphics objects stuff

		// Clear spritesheets
		for (Framework::Spritesheet* spritesheet_ptr : graphics_objects.spritesheet_ptrs) {
			delete spritesheet_ptr;
		}
		graphics_objects.spritesheet_ptrs.clear();

		// Clear images
		for (Framework::Image* image_ptr : graphics_objects.image_ptrs) {
			image_ptr->free();
			delete image_ptr;
		}
		graphics_objects.image_ptrs.clear();

		// Clear fonts
		for (Framework::Font* font_ptr : graphics_objects.font_ptrs) {
			delete font_ptr;
		}
		graphics_objects.font_ptrs.clear();

		// Clear transitions
		for (Framework::BaseTransition* transition_ptr : graphics_objects.transition_ptrs) {
			delete transition_ptr;
		}
		graphics_objects.transition_ptrs.clear();

		
		// Destroy renderer and window
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
	}
}