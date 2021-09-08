#pragma once

#include "SDL.h"
#include "SDL_image.h"

//#include <stdio.h>
#include <string>
//#include <array>


#include "Constants.hpp"

#include "Spritesheet.hpp"
#include "InputManager.hpp"
#include "ParticleManager.hpp"
#include "TimerManager.hpp"
#include "TextManager.hpp"
#include "LevelManager.hpp"

//#include "Bezier.hpp"
//#include "Utilities.hpp"

//#include "Player.hpp"

//#include "Assets.hpp"


// Game class

class Game {
public:
	Game();

	uint8_t run();

private:
	bool init();
	void quit();

	void load_data();
	void clear_data();

	std::string find_assets_path(std::string test_file, uint8_t depth = 4);

	void update(float dt);
	void render();

	// Update and render functions for each state
	void update_menu_intro(float dt);
	void render_menu_intro();

	void update_menu_title(float dt);
	void render_menu_title();

	/*void update_menu_settings(float dt);
	void render_menu_settings();*/

	// Setup functions for each state
	void setup_menu_intro();
	void setup_menu_title();
	//void setup_menu_settings();


	// Loading functions
	SDL_Texture* load_texture(std::string path);
	SDL_Surface* load_surface(std::string path);


	enum class GameState {
		MENU_INTRO,
		MENU_TITLE
	};


	// Variables

	// Main game window
	SDL_Window* window = NULL;

	// Renderer for window
	SDL_Renderer* renderer = NULL;

	// Spritesheet
	SDL_Texture* spritesheet_texture = NULL;
	Spritesheet spritesheet;

	// Fonts
	SDL_Texture* font_sheet_texture = NULL;
	FontHandler::Font font_white;

	// Input handler
	InputHandler input_handler;

	// Particle handler
	struct {
		ParticleHandler back, front, spare;
	} particle_handlers;

	// Timer handler
	TimerHandler timer_handler;

	// Player
	//Player player;

	// Level handler
	LevelHandler level_handler;


	// State/data variables

	// Game state
	GameState game_state = GameState::MENU_INTRO;

	bool running = false;

	uint8_t option_selected = 0;
	bool option_confirmed = false;

	/*struct {
		bool audio_music = true;
		bool audio_sfx = true;
	} settings;*/
};