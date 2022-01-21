#include "SDL2Extras.hpp"

namespace Framework::SDL2Extras {

	bool init_sdl(SDL_Window*& window, SDL_Renderer*& renderer) {
		// Initialise SDL
		if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			printf("SDL could not initialize!\nSDL Error: %s\n", SDL_GetError());
			return false;
		}

		// Initialise SDL_image
		int img_init_flags = IMG_INIT_JPG | IMG_INIT_PNG;
		if ((IMG_Init(img_init_flags) & img_init_flags) != img_init_flags) {
			printf("SDL_IMG could not initialize!\nSDL_IMG Error: %s\n", IMG_GetError());
			return false;
		}

		// Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		// Create window
		window = SDL_CreateWindow(
			WINDOW::TITLE,
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			WINDOW::WIDTH,
			WINDOW::HEIGHT,
			SDL_WINDOW_SHOWN
		);

		// Create renderer for window
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

		// Set renderer mode
		SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

		return (renderer != nullptr && window != nullptr);
	}
}