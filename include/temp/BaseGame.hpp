#pragma once

#include "SDL.h"
#include "SDL_image.h"

#include <string>

#include "Constants.hpp"

#include "InputManager.hpp"
#include "AudioManager.hpp"
#include "DataManager.hpp"
#include "TextManager.hpp"
#include "GraphicsManager.hpp"

// Base Game class

class BaseGame {
public:
	BaseGame();

	bool run();

protected:
	void init();
	void quit();

	void load_data();
	void clear_data();

	virtual void update(float dt) = 0;
	virtual void render() = 0;

	// Called just before entering main game loop for first time.
	virtual void start() = 0;
	virtual void end() = 0;

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

	// Timer handler
	TimerHandler timer_handler;
};