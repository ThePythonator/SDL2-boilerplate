#pragma once

#include "SDL.h"
#include "SDL_image.h"

#include <cstdio>
#include <string>

#include "Constants.hpp"

#include "Maths.hpp"

namespace Framework::SDLUtils {

	// Initialises necessary SDL bits, and assigns window and renderer.
	bool init_sdl(SDL_Window*& window, SDL_Renderer*& renderer);

	std::string find_assets_path(std::string test_file, uint8_t depth);

	int SDL_SetRenderDrawColor(SDL_Renderer* renderer, const Colour& colour);

	void SDL_SetTextureColorMod(SDL_Texture* texture, const Colour& colour);

	void SDL_SetPixel(SDL_Surface* surface, int x, int y, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
	void SDL_SetPixel(SDL_Surface* surface, int x, int y, const Colour& colour);

	void SDL_GetPixel(SDL_Surface* surface, int x, int y, uint8_t* r, uint8_t* g, uint8_t* b, uint8_t* a);
	Colour SDL_GetPixel(SDL_Surface* surface, int x, int y);

	int SDL_RenderDrawCircle(SDL_Renderer* renderer, int x, int y, int radius);

	SDL_Rect get_sdl_rect(Rect rect);
	SDL_Point get_sdl_point(vec2 vec);
	SDL_RendererFlip get_sdl_renderer_flip(ImageFlip flip);
}