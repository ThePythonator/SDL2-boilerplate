#pragma once

#include "SDL.h"
#include "SDL_image.h"

//#include <cstdint>
//#include <cstdio>
#include <string>

namespace Framework {
	class Image {
	public:
		Image();

		bool load(std::string path);
		void free();

		SDL_Texture* get_image();

	private:
		SDL_Texture* image = nullptr;
	};
}