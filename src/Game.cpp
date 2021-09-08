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

Game::Game() {

}

// Methods

bool Game::init() {
	// Initialise SDL
	int sdl_init_result = SDL_Init(SDL_INIT_VIDEO);
	if (sdl_init_result < 0)
	{
		printf("SDL could not initialize!\nSDL Error: %s\n", SDL_GetError());
		return false;
	}

	// Initialise SDL_image
	int img_init_flags = IMG_INIT_JPG | IMG_INIT_PNG;
	int img_init_result = IMG_Init(img_init_flags);
	if ((img_init_result & img_init_flags) != img_init_flags) {
		printf("SDL_IMG could not initialize!\nSDL_IMG Error: %s\n", IMG_GetError());
		return false;
	}

	// Set texture filtering to linear
	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0"))
	{
		printf("Warning: Linear texture filtering not enabled!");
	}

	// Create window
	window = SDL_CreateWindow(
		STRINGS::APP_TITLE.c_str(),
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		WINDOW::WIDTH,
		WINDOW::HEIGHT,
		SDL_WINDOW_SHOWN
	);

	// Create renderer for window
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	// Set renderer colour and mode
	SDL_SetRenderDrawColor(renderer, COLOURS::BLACK);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

	return true;
}

void Game::quit() {
	// Destroy assets
	clear_data();

	// Destroy renderer
	SDL_DestroyRenderer(renderer);
	renderer = NULL;

	// Destroy window
	SDL_DestroyWindow(window);
	window = NULL;

	// Quit SDL
	IMG_Quit();
	SDL_Quit();
}

void Game::load_data() {
	// Uses spritesheet_texture as a test to check whether we can find the assets folder.
	std::string assets_path = find_assets_path(FILES::SPRITESHEET);

	// Load data such as images
	spritesheet_texture = load_texture(assets_path + FILES::SPRITESHEET);
	font_sheet_texture = load_texture(assets_path + FILES::FONT_SHEET);

	spritesheet = Spritesheet(renderer, spritesheet_texture, SPRITES::SIZE, SPRITES::SCALE);

	SDL_Surface* font_sheet_surface = load_surface(assets_path + FILES::FONT_SHEET);

	font_white = FontHandler::Font(renderer, font_sheet_surface, SPRITES::SIZE, SPRITES::TEXT_SCALE, COLOURS::WHITE);

	SDL_FreeSurface(font_sheet_surface);

	// Load timers
	TIMER_ID::INTRO_LENGTH = timer_handler.add_timer();

	//level_handler = LevelHandler(SPRITES::SIZE);
}

void Game::clear_data() {
	// Free loaded data such as images
	SDL_DestroyTexture(spritesheet_texture);
	spritesheet_texture = NULL;

	SDL_DestroyTexture(font_sheet_texture);
	font_sheet_texture = NULL;
}

std::string Game::find_assets_path(std::string test_file, uint8_t depth) {
	std::string base_path = SDL_GetBasePath();
	SDL_Surface* test_surface = load_surface("assets/" + test_file);

	if (test_surface != NULL) {
		base_path = "";
	}

	uint8_t count = 0;
	while (test_surface == NULL && count < depth) {
		test_surface = load_surface(base_path + "assets/" + test_file);

		if (test_surface == NULL) {
			base_path += "../";
		}

		count++;
	}

	if (test_surface == NULL) {
		return "assets/";
	}

	SDL_FreeSurface(test_surface);

	return base_path + "assets/";
}

uint8_t Game::run()
{
	// Initialise SDL and globals - if it fails, don't run program
	running = init();

	load_data();

	// Main game loop variables
	float dt = 0.0f;
	uint32_t last_time = SDL_GetTicks();
	uint32_t time = 0;

	SDL_Event sdl_event;

	setup_menu_intro();

	// Main game loop
	while (running) {
		// Update input handler (updates all key states etc)
		input_handler.update();

		// Handle events
		while (SDL_PollEvent(&sdl_event) != 0) {
			if (sdl_event.type == SDL_QUIT) {
				// X (close) is pressed
				running = false;
			}
			else {
				// Delegate to InputHandler
				input_handler.handle_sdl_event(sdl_event);
			}
		}

		// Calculate dt
		time = SDL_GetTicks();
		dt = (time - last_time) / 1000.0f;
		last_time = time;

		update(dt);

		// Clear the screen
		SDL_SetRenderDrawColor(renderer, COLOURS::BLACK);
		SDL_RenderClear(renderer);

		// Render game
		render();

		// Update screen
		SDL_RenderPresent(renderer);

		// Limit framerate - to fix
		//if (dt < MIN_DT) {
		//	// Wait remaining time
		//	SDL_Delay(1000 * (MIN_DT - dt));
		//}


		//printf("FPS: %f\n", 1.0f / dt);
	}

	// Quit everything
	quit();

	return 0;
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
	SDL_Rect src_rect{ 0, 224, 32, 32 };
	spritesheet.rect(&src_rect, WINDOW::WIDTH / 16.0f - SPRITE::SIZE, WINDOW::HEIGHT / 16.0f - SPRITE::SIZE, 8);
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





SDL_Texture* Game::load_texture(std::string path) {
	// Load image at specified path
	SDL_Surface* image = IMG_Load(path.c_str());

	if (image == NULL)
	{
		printf("Unable to create texture from %s!\nSDL Error: %s\n", path.c_str(), SDL_GetError());
	}

	// Create texture from image
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, image);

	if (texture == NULL)
	{
		printf("Unable to create texture from %s!\nSDL Error: %s\n", path.c_str(), SDL_GetError());
	}

	// Get rid of old loaded surface
	SDL_FreeSurface(image);

	return texture;
}

SDL_Surface* Game::load_surface(std::string path) {
	// Load image at specified path
	SDL_Surface* image = IMG_Load(path.c_str());

	if (image == NULL)
	{
		printf("Unable to load image %s!\nSDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}

	return image;
}