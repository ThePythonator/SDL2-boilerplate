#pragma once

#include "SDL.h"
#include "SDL_image.h"

#include <string>

std::string find_assets_path(std::string test_file, uint8_t depth = 4);

// Loading functions
SDL_Texture* load_texture(std::string path, SDL_Renderer* renderer);
SDL_Surface* load_surface(std::string path);