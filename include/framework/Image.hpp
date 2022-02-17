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
			SDL_SURFACE = 0b10,

			ALL = SDL_TEXTURE | SDL_SURFACE
		};

		Image(Graphics* graphics);

		bool load(std::string path, uint8_t flags = Flags::ALL);
		void free();

		bool refresh(uint8_t source_flag);

		void render(Rect source_rect, Rect destination_rect, float angle, vec2 centre, ImageFlip flip = ImageFlip::FLIP_NONE);
		void render(Rect source_rect, Rect destination_rect, float angle, ImageFlip flip = ImageFlip::FLIP_NONE);
		void render(Rect source_rect, Rect destination_rect);
		void render(Rect destination_rect);

		SDL_Texture* get_texture();
		SDL_Surface* get_surface();

		vec2 get_size();

	private:
		SDL_Texture* texture = nullptr;
		SDL_Surface* surface = nullptr;

		Graphics* graphics_ptr = nullptr;

		uint8_t types = Flags::NONE;

		uint32_t _w = 0;
		uint32_t _h = 0;
	};

	Image* create_image(Graphics* graphics, std::string path, uint8_t flags = Image::Flags::ALL);
}