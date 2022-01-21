#pragma once

#include <string>

#include "SDL.h"
#include "SDL_image.h"

#include "Graphics.hpp"

namespace Framework {
	class Image {
	public:
		enum Flags : uint8_t {
			NONE = 0b00,

			SDL_TEXTURE = 0b01,
			SDL_SURFACE = 0b10
		};

		Image();

		bool load(Graphics* graphics, std::string path, uint8_t flags = Flags::SDL_TEXTURE);
		void free();

		SDL_Texture* get_texture();
		SDL_Surface* get_surface();

	private:
		SDL_Texture* texture = nullptr;
		SDL_Surface* surface = nullptr;

		uint8_t types = Flags::NONE;
	};
}