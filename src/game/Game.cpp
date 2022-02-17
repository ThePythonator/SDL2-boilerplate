#include "Game.hpp"

Game::Game() : BaseGame() {

}

void Game::start() {
	stage = new TitleStage();
}

void Game::end() {

}

void Game::load_data() {
	std::string ASSETS_PATH = Framework::SDLUtils::find_assets_path(PATHS::IMAGES::LOCATION + PATHS::IMAGES::MAIN_SPRITESHEET, PATHS::DEPTH);
	graphics_objects.asset_path = ASSETS_PATH;
	std::string IMAGES_PATH = ASSETS_PATH + PATHS::IMAGES::LOCATION;

	// Load spritesheet image
	graphics_objects.image_ptrs[GRAPHICS_OBJECTS::IMAGES::MAIN_SPRITESHEET] = Framework::create_image(graphics_objects.graphics_ptr, IMAGES_PATH + PATHS::IMAGES::MAIN_SPRITESHEET, Framework::Image::Flags::SDL_TEXTURE);
	
	// Load font image
	// Note: we *need* to add SURFACE flags because Font uses the surface bit
	graphics_objects.image_ptrs[GRAPHICS_OBJECTS::IMAGES::FONT_SPRITESHEET] = Framework::create_image(graphics_objects.graphics_ptr, IMAGES_PATH + PATHS::IMAGES::FONT_SPRITESHEET, Framework::Image::Flags::SDL_TEXTURE | Framework::Image::Flags::SDL_SURFACE);
	
	// Create spritesheet from spritesheet image
	graphics_objects.spritesheet_ptrs[GRAPHICS_OBJECTS::SPRITESHEETS::MAIN_SPRITESHEET] = new Framework::Spritesheet(graphics_objects.graphics_ptr, graphics_objects.image_ptrs[GRAPHICS_OBJECTS::IMAGES::MAIN_SPRITESHEET], SPRITE::SIZE, SPRITE::SCALE);

	// Create spritesheet from font image
	graphics_objects.spritesheet_ptrs[GRAPHICS_OBJECTS::SPRITESHEETS::FONT_SPRITESHEET] = new Framework::Spritesheet(graphics_objects.graphics_ptr, graphics_objects.image_ptrs[GRAPHICS_OBJECTS::IMAGES::FONT_SPRITESHEET], FONTS::SIZE::MAIN_FONT, FONTS::SCALE::MAIN_FONT);

	// Create font from font spritesheet
	graphics_objects.font_ptrs[GRAPHICS_OBJECTS::FONTS::MAIN_FONT] = new Framework::Font(graphics_objects.graphics_ptr, graphics_objects.spritesheet_ptrs[GRAPHICS_OBJECTS::SPRITESHEETS::FONT_SPRITESHEET], FONTS::SPACING::MAIN_FONT);
	
	// Create transitions
	graphics_objects.transition_ptrs[GRAPHICS_OBJECTS::TRANSITIONS::FADE_TRANSITION] = new Framework::FadeTransition(COLOURS::BLACK, TRANSITIONS::FADE_TIME);
}

void Game::clear_data() {
	// Don't need to clear up graphics objects items - it's done for us in BaseGame

	// Clear up anything else we need to
}