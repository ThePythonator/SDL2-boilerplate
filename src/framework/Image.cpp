#include "Image.hpp"

namespace Framework {
	Image::Image(Graphics* graphics) {
		graphics_ptr = graphics;
	}

	bool Image::load(std::string path, uint8_t flags) {
		// Load image at specified path
		SDL_Surface* temp_surface = IMG_Load(path.c_str());

		if (temp_surface == NULL)
		{
			printf("Unable to create surface from %s!\nSDL Error: %s\n", path.c_str(), SDL_GetError());
			return false;
		}

		// Get width and height
		_w = temp_surface->w;
		_h = temp_surface->h;

		// Create texture from image
		SDL_Texture* temp_texture = SDL_CreateTextureFromSurface(graphics_ptr->get_renderer(), temp_surface);

		if (temp_texture == NULL)
		{
			printf("Unable to create texture from %s!\nSDL Error: %s\n", path.c_str(), SDL_GetError());
			SDL_FreeSurface(temp_surface);
			return false;
		}

		if (flags & Flags::SDL_SURFACE) {
			// We want to keep the surface
			surface = temp_surface;
			types |= Flags::SDL_SURFACE; // set bit
		}
		else {
			// Free
			SDL_FreeSurface(temp_surface);
		}

		if (flags & Flags::SDL_TEXTURE) {
			// We want to keep the surface
			texture = temp_texture;
			types |= Flags::SDL_TEXTURE; // Set bit
		}
		else {
			// Free
			SDL_DestroyTexture(temp_texture);
		}

		return true;
	}

	void Image::free() {
		// Free the images
		if (types & Flags::SDL_SURFACE) {
			SDL_FreeSurface(surface);
			types &= ~Flags::SDL_SURFACE; // Unset bit
		}
		if (types & Flags::SDL_TEXTURE) {
			SDL_DestroyTexture(texture);
			types &= ~Flags::SDL_TEXTURE; // Unset bit
		}
	}

	bool Image::refresh(uint8_t source_flag) {
		// Refresh and update texture/surface using either the image's texture or surface

		// Don't allow source_flag to have multiple sources
		if (source_flag == Flags::SDL_SURFACE) {
			// Update texture from surface
			// Check we actually have a surface stored
			if (types & Flags::SDL_SURFACE) {
				// Create texture from the stored surface
				SDL_Texture* temp_texture = SDL_CreateTextureFromSurface(graphics_ptr->get_renderer(), surface);

				if (temp_texture == NULL)
				{
					printf("Unable to convert surface to texture!\nSDL Error: %s\n", SDL_GetError());
					return false;
				}
				else {
					texture = temp_texture;
					return true;
				}
			}
			else {
				// Don't have a surface available
				return false;
			}
		}
		else if (source_flag == Flags::SDL_TEXTURE) {
			// Updates surface from texture
			// Not supported by SDL
			return false;
		}
		else {
			// Multiple or no sources, or not supported
			return false;
		}

		/*// First check, source_flag > 0, then check it is an exact power of two
		// n & (n-1) returns 0 if n is an exact power of two, so we need to invert it
		if (source_flag && !(source_flag & (source_flag - 1))) {
			// todo
			return true;
		}
		else {
			return false;
		}*/
	}

	void Image::render(Rect source_rect, Rect destination_rect, float angle, vec2 centre, ImageFlip flip) {
		// If size is unset, default to Image's size
		if (source_rect.size == vec2{ 0.0f, 0.0f })			source_rect.size = get_size();
		if (destination_rect.size == vec2{ 0.0f, 0.0f })	destination_rect.size = get_size();

		SDL_Rect* sdl_src_rect_ptr = &SDLUtils::get_sdl_rect(source_rect);
		SDL_Rect* sdl_dst_rect_ptr = &SDLUtils::get_sdl_rect(destination_rect);

		SDL_Point* sdl_centre_ptr = &SDLUtils::get_sdl_point(centre);

		SDL_RenderCopyEx(graphics_ptr->get_renderer(), texture, sdl_src_rect_ptr, sdl_dst_rect_ptr, angle, sdl_centre_ptr, SDLUtils::get_sdl_renderer_flip(flip));
	}

	void Image::render(Rect source_rect, Rect destination_rect, float angle, ImageFlip flip) {
		// If size is unset, default to Image's size
		if (source_rect.size == vec2{ 0.0f, 0.0f })			source_rect.size = get_size();
		if (destination_rect.size == vec2{ 0.0f, 0.0f })	destination_rect.size = get_size();

		render(source_rect, destination_rect, angle, destination_rect.size / 2, flip); // todo?
	}

	void Image::render(Rect source_rect, Rect destination_rect) {
		// If size is unset, default to Image's size
		if (source_rect.size == vec2{ 0.0f, 0.0f })			source_rect.size = get_size();
		if (destination_rect.size == vec2{ 0.0f, 0.0f })	destination_rect.size = get_size();

		SDL_Rect* sdl_src_rect_ptr = &SDLUtils::get_sdl_rect(source_rect);
		SDL_Rect* sdl_dst_rect_ptr = &SDLUtils::get_sdl_rect(destination_rect);

		// Render from texture to screen
		SDL_RenderCopy(graphics_ptr->get_renderer(), texture, sdl_src_rect_ptr, sdl_dst_rect_ptr);
	}

	void Image::render(Rect destination_rect) {
		render(RECT_NULL, destination_rect);
	}

	// Returns SDL_Texture* if loaded, otherwise returns nullptr
	SDL_Texture* Image::get_texture() {
		return texture;
	}

	// Returns SDL_Surface* if loaded, otherwise returns nullptr
	SDL_Surface* Image::get_surface() {
		return surface;
	}

	vec2 Image::get_size() {
		return vec2{ static_cast<float>(_w), static_cast<float>(_h)};
	}

	Image* create_image(Graphics* graphics, std::string path, uint8_t flags) {
		Image* image_ptr = new Image(graphics);
		image_ptr->load(path, flags);
		return image_ptr;
	}
}