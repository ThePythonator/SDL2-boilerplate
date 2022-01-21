#include "Image.hpp"

namespace Framework {
	Image::Image() {

	}

	bool Image::load(std::string path) {
		// TODO: param Graphics, but currently graphics will handle rendering... :|
		// TODO: flags? tell whether to load surface, texture or both??
		// TODO:	- or just always load both?? or just texture??
		// TODO:		- if so, need access functions for both


	//bool Image::load(Graphics graphics, std::string path, uint8_t flags) {
		// Load image at specified path
		//SDL_Surface* surface = IMG_Load(path.c_str());

		//if (surface == NULL)
		//{
		//	printf("Unable to create texture from %s!\nSDL Error: %s\n", path.c_str(), SDL_GetError());
		//}

		//// Create texture from image
		//SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

		//if (texture == NULL)
		//{
		//	printf("Unable to create texture from %s!\nSDL Error: %s\n", path.c_str(), SDL_GetError());
		//}

		//// Get rid of old loaded surface
		//SDL_FreeSurface(surface);

		//return texture;
	}

	void Image::free() {
		// free the stuff
	}


	SDL_Texture* Image::get_image() {
		return image;
	}
}