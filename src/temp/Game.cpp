#include "Game.hpp"

//namespace GAME {
//	const uint8_t LEVEL_COUNT = 12;
//}

namespace MENU {
	enum class TITLE : uint8_t {
		PLAY,
		//SETTINGS,
		QUIT,

		OPTION_COUNT
	};

	/*enum class SETTINGS : uint8_t {
		MUSIC,
		SFX,
		BACK,

		OPTION_COUNT
	};*/
}

Game::Game() : BaseGame() {

}

// Methods

void Game::load_data() {
	// Load basic data e.g. spritesheets etc
	BaseGame::load_data();

	// Load timers
	TIMER_ID::INTRO_LENGTH = timer_handler.add_timer();

	//level_handler = LevelHandler(SPRITES::SIZE);
}

void Game::clear_data() {
	// Clear basic data e.g. spritesheets etc
	BaseGame::clear_data();

	// Handle tidy-up of other stuff here
}

void Game::start() {
	setup_menu_intro();
}

void Game::end() {
	// Handle end of game here
}

void Game::update(float dt) {
	// Update timers
	timer_handler.update(dt);

	// Update particles
	particle_handlers.back.update(dt);
	particle_handlers.spare.update(dt);
	particle_handlers.front.update(dt);

	switch (game_state) {
	case GameState::MENU_INTRO:
		update_menu_intro(dt);
		break;
	case GameState::MENU_TITLE:
		update_menu_title(dt);
		break;
	default:
		break;
	}
}

void Game::render() {
	// Render particles
	particle_handlers.back.render(spritesheet);

	switch (game_state) {
	case GameState::MENU_INTRO:
		render_menu_intro();
		break;
	case GameState::MENU_TITLE:
		render_menu_title();
		break;
	default:
		break;
	}

	// Render particles
	particle_handlers.front.render(spritesheet);
}

// Update and render functions for each state
void Game::update_menu_intro(float dt) {
	
}

void Game::render_menu_intro() {
	// Display logo
	// DON'T USE SDL STUFF
	//SDL_Rect src_rect{ 0, 224, 32, 32 };
	//spritesheet.rect(&src_rect, WINDOW::WIDTH / 16.0f - SPRITE::SIZE, WINDOW::HEIGHT / 16.0f - SPRITE::SIZE, 8);
}

void Game::update_menu_title(float dt) {
	
}

void Game::render_menu_title() {
	//TextHandler::render_text(option_selected == 0 ? font_selected : font_white, STRINGS::MENU::TITLE::OPTION_PLAY, left_x, WINDOW::TEXT_SCALED_HEIGHT_HALF - SPRITES::SIZE * 2, SPRITES::SPACE_WIDTH);
}

void Game::setup_menu_intro() {
	game_state = GameState::MENU_INTRO;
}

void Game::setup_menu_title() {
	game_state = GameState::MENU_TITLE;
}