#pragma once

#include "SDL.h"

#include "SDLUtils.hpp"

#include "Colour.hpp"

namespace Framework {
	class Graphics {
	public:
		Graphics();

		void fill(const Colour& colour);
		void fill(const Colour& colour, uint8_t alpha);

		void set_renderer(SDL_Renderer* _renderer);
		SDL_Renderer* get_renderer();

	private:
		SDL_Renderer* renderer = nullptr;
	};
}