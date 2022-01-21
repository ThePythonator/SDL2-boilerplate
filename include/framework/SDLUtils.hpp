#pragma once

#include "SDL.h"
#include "SDL_image.h"

#include <cstdio>

#include "Constants.hpp"

namespace Framework::SDLUtils {

	// Initialises necessary SDL bits, and assigns window and renderer.
	bool init_sdl(SDL_Window*& window, SDL_Renderer*& renderer);

	int SDL_SetRenderDrawColor(SDL_Renderer* renderer, const Colour& colour);

	int SDL_RenderDrawCircle(SDL_Renderer* renderer, int x, int y, int radius);
}