#pragma once

#include <vector>

#include "Graphics.hpp"
#include "Window.hpp"

#include "Image.hpp"
#include "Spritesheet.hpp"
#include "Font.hpp"
#include "BaseTransition.hpp"
#include "Button.hpp"

namespace Framework {
	struct GraphicsObjects {
		Graphics graphics;
		Window window;

		std::vector<Image*> image_ptrs;
		std::vector<Spritesheet> spritesheets;
		std::vector<Font> fonts;
		std::vector<BaseTransition*> transition_ptrs;

		std::vector<Button::ButtonImages> button_image_groups;
	};
}