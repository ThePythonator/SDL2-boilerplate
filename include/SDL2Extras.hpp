#pragma once

#include "SDL.h"
#include "SDL_image.h"

#include <cstdio>

#include "Constants.hpp"

namespace Framework::SDL2Extras {

	// Initialises necessary SDL bits, and assigns window and renderer.
	bool init_sdl(SDL_Window* window, SDL_Renderer* renderer);
}