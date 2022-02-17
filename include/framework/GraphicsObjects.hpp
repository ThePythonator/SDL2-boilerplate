#pragma once

#include <vector>

#include "Graphics.hpp"

#include "Image.hpp"
#include "Spritesheet.hpp"
#include "Font.hpp"
#include "BaseTransition.hpp"

namespace Framework {
	struct GraphicsObjects {
		Graphics* graphics_ptr = nullptr;

		std::vector<Image*> image_ptrs;
		std::vector<Spritesheet*> spritesheet_ptrs;
		std::vector<Font*> font_ptrs;
		std::vector<BaseTransition*> transition_ptrs;

		std::string asset_path;
	};
}