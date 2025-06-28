#include "Game.hpp"

Game::Game() : BaseGame() {

}

void Game::start() {
	stage = new IntroStage();
}

void Game::end() {

}

void Game::load_data() {
	// TODO: Should this be set to PATHS::BASE_PATH? If so, that requires importing Constants.hpp
	std::string BASE_PATH = Framework::SDLUtils::find_base_directory(PATHS::IMAGES::LOCATION + PATHS::IMAGES::MAIN_SPRITESHEET, PATHS::DEPTH);
	
	// Base path is two above images path
	std::string IMAGES_PATH = BASE_PATH + PATHS::IMAGES::LOCATION;

	// Load spritesheet image
	graphics_objects.image_ptrs[GRAPHICS_OBJECTS::IMAGES::MAIN_SPRITESHEET] = Framework::create_image(&graphics_objects.graphics, IMAGES_PATH + PATHS::IMAGES::MAIN_SPRITESHEET, Framework::Image::Flags::SDL_TEXTURE);

	// Load font image
	// Note: we *need* to add SURFACE flags because Font uses the surface bit
	graphics_objects.image_ptrs[GRAPHICS_OBJECTS::IMAGES::FONT_SPRITESHEET] = Framework::create_image(&graphics_objects.graphics, IMAGES_PATH + PATHS::IMAGES::FONT_SPRITESHEET, Framework::Image::Flags::SDL_TEXTURE | Framework::Image::Flags::SDL_SURFACE);
	
	// Create spritesheet from spritesheet image
	graphics_objects.spritesheets[GRAPHICS_OBJECTS::SPRITESHEETS::MAIN_SPRITESHEET] = Framework::Spritesheet(graphics_objects.image_ptrs[GRAPHICS_OBJECTS::IMAGES::MAIN_SPRITESHEET].get(), SPRITES::SIZE, SPRITES::SCALE);

	// Create spritesheet from font image
	graphics_objects.spritesheets[GRAPHICS_OBJECTS::SPRITESHEETS::FONT_SPRITESHEET] = Framework::Spritesheet(graphics_objects.image_ptrs[GRAPHICS_OBJECTS::IMAGES::FONT_SPRITESHEET].get(), FONTS::SIZE::MAIN_FONT, FONTS::SCALE::MAIN_FONT);

	// Create font from font spritesheet
	graphics_objects.fonts[GRAPHICS_OBJECTS::FONTS::MAIN_FONT] = Framework::Font(&graphics_objects.spritesheets[GRAPHICS_OBJECTS::SPRITESHEETS::FONT_SPRITESHEET], FONTS::SPACING::MAIN_FONT);
	
	// Load button images
	graphics_objects.image_ptrs[GRAPHICS_OBJECTS::IMAGES::STANDARD_BUTTON_UNSELECTED] = Framework::create_image(&graphics_objects.graphics, Framework::Vec(64, 16));
	graphics_objects.image_ptrs[GRAPHICS_OBJECTS::IMAGES::STANDARD_BUTTON_HOVERED] = Framework::create_image(&graphics_objects.graphics, Framework::Vec(64, 16));
	graphics_objects.image_ptrs[GRAPHICS_OBJECTS::IMAGES::STANDARD_BUTTON_SELECTED] = Framework::create_image(&graphics_objects.graphics, Framework::Vec(64, 16));

	// TODO: also could change into a single function to create an image from a spritesheet
	graphics_objects.button_image_groups[GRAPHICS_OBJECTS::BUTTON_IMAGE_GROUPS::STANDARD] = {
		.unselected = graphics_objects.image_ptrs[GRAPHICS_OBJECTS::IMAGES::STANDARD_BUTTON_UNSELECTED].get(),
		.hovered    = graphics_objects.image_ptrs[GRAPHICS_OBJECTS::IMAGES::STANDARD_BUTTON_HOVERED].get(),
		.selected   = graphics_objects.image_ptrs[GRAPHICS_OBJECTS::IMAGES::STANDARD_BUTTON_SELECTED].get(),
	};

	graphics_objects.button_image_groups[GRAPHICS_OBJECTS::BUTTON_IMAGE_GROUPS::STANDARD].unselected->set_render_target();
	graphics_objects.spritesheets[GRAPHICS_OBJECTS::SPRITESHEETS::MAIN_SPRITESHEET].rect(Framework::Rect(0, 16, 64, 16), Framework::Vec(0, 0), 1.0f);

	graphics_objects.button_image_groups[GRAPHICS_OBJECTS::BUTTON_IMAGE_GROUPS::STANDARD].hovered->set_render_target();
	graphics_objects.spritesheets[GRAPHICS_OBJECTS::SPRITESHEETS::MAIN_SPRITESHEET].rect(Framework::Rect(0, 32, 64, 16), Framework::Vec(0, 0), 1.0f);

	graphics_objects.button_image_groups[GRAPHICS_OBJECTS::BUTTON_IMAGE_GROUPS::STANDARD].selected->set_render_target();
	graphics_objects.spritesheets[GRAPHICS_OBJECTS::SPRITESHEETS::MAIN_SPRITESHEET].rect(Framework::Rect(0, 48, 64, 16), Framework::Vec(0, 0), 1.0f);

	Framework::SDLUtils::SDL_UnsetRenderTarget(graphics_objects.graphics.get_renderer());


	// Create transitions
	graphics_objects.transition_ptrs[GRAPHICS_OBJECTS::TRANSITIONS::FADE_TRANSITION] = std::make_unique<Framework::FadeTransition>(&graphics_objects.graphics, COLOURS::BLACK, TRANSITIONS::FADE_TIME);
}

void Game::clear_data() {
	// Don't need to clear up graphics objects items - it's done for us in BaseGame

	// Clear up anything else we need to
}
