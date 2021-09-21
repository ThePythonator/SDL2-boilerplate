#pragma once

#include <string>

#include "BaseGame.hpp"


#include "Constants.hpp"

#include "ParticleManager.hpp"
#include "LevelManager.hpp"


// Game class

class Game : public BaseGame {
public:
	Game();

private:

	void load_data();
	void clear_data();

	void start();
	void end();

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


	enum class GameState {
		MENU_INTRO,
		MENU_TITLE
	};


	// Variables

	// Particle handler
	struct {
		ParticleHandler back, front, spare;
	} particle_handlers;

	// Level handler
	LevelHandler level_handler;


	// State/data variables

	// Game state
	GameState game_state = GameState::MENU_INTRO;

	uint8_t option_selected = 0;
	bool option_confirmed = false;

	/*struct {
		bool audio_music = true;
		bool audio_sfx = true;
	} settings;*/
};