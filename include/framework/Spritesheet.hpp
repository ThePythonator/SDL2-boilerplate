#pragma once

#include "Image.hpp"
#include "Transform.hpp"

class Spritesheet {
public:
	Spritesheet();
	Spritesheet(Graphics* graphics, Image* spritesheet_image, uint8_t sprite_size = 16, uint8_t scale = 1);

	//void sprite(uint16_t index, float x, float y, float scale = 1.0f);
	//void sprite(uint16_t index, float x, float y, float scale, SDL_RendererFlip flip);
	//void sprite(uint16_t index, float x, float y, float scale, float angle, SDL_Point* center, SDL_RendererFlip flip = SDL_RendererFlip::SDL_FLIP_NONE);

	//void sprite_scaled(uint16_t index, float x, float y);
	//void sprite_scaled(uint16_t index, float x, float y, SDL_RendererFlip flip);
	//void sprite_scaled(uint16_t index, float x, float y, float angle, SDL_Point* center, SDL_RendererFlip flip = SDL_RendererFlip::SDL_FLIP_NONE);

	//void rect(SDL_Rect* src_rect, float x, float y);
	//void rect(SDL_Rect* src_rect, float x, float y, float scale);

	//void rect_scaled(SDL_Rect* src_rect, float x, float y);


	//void set_blend_mode(SDL_BlendMode blending);
	//void set_alpha(uint8_t alpha);


	//float get_scale();
	//uint8_t get_alpha();

	//SDL_Texture* get_texture();

	//uint8_t get_sprite_size();

private:
	//SDL_Renderer* renderer = nullptr;

	//SDL_Texture* spritesheet_texture = nullptr;

	uint32_t w, h;
	uint8_t rows, columns;

	//uint8_t sprite_size;

	//uint8_t scale;
};