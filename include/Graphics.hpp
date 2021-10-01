#pragma once

#include "SDL2.h"

#include "Image.hpp"
#include "Spritesheet.hpp"
#include "Text.hpp"
#include "Colour.hpp"

namespace Framework {
	class Graphics {
	public:

	private:
		SDL_Renderer* renderer = nullptr;
	};
}