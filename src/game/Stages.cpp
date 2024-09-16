#include "Stages.hpp"

// TitleStage

void TitleStage::start() {
	// Create buttons
	buttons.clear();
	buttons.emplace_back(
		Framework::Rect(WINDOW::SIZE_HALF - Framework::Vec(128, 32), Framework::Vec(256, 64)),
		graphics_objects->button_image_groups[GRAPHICS_OBJECTS::BUTTON_IMAGE_GROUPS::STANDARD],
		Framework::Text(graphics_objects->font_ptrs[GRAPHICS_OBJECTS::FONTS::MAIN_FONT], "Play", COLOURS::BLACK, 4.0f),
		BUTTONS::TITLE::PLAY
	);
	buttons.emplace_back(
		Framework::Rect(WINDOW::SIZE_HALF - Framework::Vec(128, -64), Framework::Vec(256, 64)),
		graphics_objects->button_image_groups[GRAPHICS_OBJECTS::BUTTON_IMAGE_GROUPS::STANDARD],
		Framework::Text(graphics_objects->font_ptrs[GRAPHICS_OBJECTS::FONTS::MAIN_FONT], "Quit", COLOURS::BLACK, 4.0f),
		BUTTONS::TITLE::QUIT
	);

	// Set transition
	set_transition(graphics_objects->transition_ptrs[GRAPHICS_OBJECTS::TRANSITIONS::FADE_TRANSITION]);

	// Start transition
	transition->open();

	// Start timer used for rotations
	_timer.start();
}

bool TitleStage::update(float dt) {
	transition->update(dt);
	_timer.update(dt);

	// Update buttons
	for (Framework::Button& button : buttons) {
		button.update(input);

		if (button.pressed() && transition->is_open()) {
			button_selected = button.get_id();
			transition->close();
		}
	}

	if (transition->is_closed()) {
		// Next stage!
		switch (button_selected) {
		case BUTTONS::TITLE::PLAY:
			finish(new GameStage());
			break;

		case BUTTONS::TITLE::QUIT:
			// Returning false causes program to exit
			return false;
			// (so we don't need the break)

		default:
			break;
		}
	}

	return true;
}

void TitleStage::render() {
	graphics_objects->graphics_ptr->fill(COLOURS::BLUE);

	graphics_objects->graphics_ptr->render_circle(Framework::Vec(20, 20), 10, COLOURS::BLACK);
	graphics_objects->graphics_ptr->render_rect(Framework::Rect(40, 20, 10, 30), COLOURS::BLACK);

	graphics_objects->spritesheet_ptrs[GRAPHICS_OBJECTS::SPRITESHEETS::MAIN_SPRITESHEET]->sprite(0, Framework::Vec(64, 48));

	graphics_objects->spritesheet_ptrs[GRAPHICS_OBJECTS::SPRITESHEETS::MAIN_SPRITESHEET]->sprite(2, Framework::Vec(16, 48));
	graphics_objects->spritesheet_ptrs[GRAPHICS_OBJECTS::SPRITESHEETS::MAIN_SPRITESHEET]->sprite(2, Framework::Vec(32, 48), Framework::SpriteTransform::ROTATE_90_ACW);

	graphics_objects->spritesheet_ptrs[GRAPHICS_OBJECTS::SPRITESHEETS::MAIN_SPRITESHEET]->sprite(1, Framework::Vec(96, 48), SPRITES::SCALE, _timer.time() * 90);

	for (const Framework::Button& button : buttons) {
		button.render();
	}

	transition->render();
}

// GameStage

void GameStage::start() {
	// Set transition
	set_transition(graphics_objects->transition_ptrs[GRAPHICS_OBJECTS::TRANSITIONS::FADE_TRANSITION]);

	// Start transition
	transition->open();
}

bool GameStage::update(float dt) {
	transition->update(dt);

	if (input->just_down(Framework::KeyHandler::Key::ESCAPE) || input->just_down(Framework::KeyHandler::Key::P)) {
		finish(new PausedStage(this), false);
	}

	return true;
}

void GameStage::render() {
	graphics_objects->graphics_ptr->fill(COLOURS::BLUE);

	graphics_objects->spritesheet_ptrs[GRAPHICS_OBJECTS::SPRITESHEETS::MAIN_SPRITESHEET]->sprite(0, Framework::Vec(128, 64));

	transition->render();
}

// PausedStage

PausedStage::PausedStage(BaseStage* background_stage) : BaseStage() {
	// Save the background stage so we can still render it, and then go back to it when done
	_background_stage = background_stage;
}

void PausedStage::start() {
	// Create buttons
	buttons.clear();
	buttons.emplace_back(
		Framework::Rect(WINDOW::SIZE_HALF - Framework::Vec(128, 32), Framework::Vec(256, 64)),
		graphics_objects->button_image_groups[GRAPHICS_OBJECTS::BUTTON_IMAGE_GROUPS::STANDARD],
		Framework::Text(graphics_objects->font_ptrs[GRAPHICS_OBJECTS::FONTS::MAIN_FONT], "Resume", COLOURS::BLACK, 4.0f),
		BUTTONS::PAUSED::RESUME
	);
	buttons.emplace_back(
		Framework::Rect(WINDOW::SIZE_HALF - Framework::Vec(128, -64), Framework::Vec(256, 64)),
		graphics_objects->button_image_groups[GRAPHICS_OBJECTS::BUTTON_IMAGE_GROUPS::STANDARD],
		Framework::Text(graphics_objects->font_ptrs[GRAPHICS_OBJECTS::FONTS::MAIN_FONT], "Exit", COLOURS::BLACK, 4.0f),
		BUTTONS::PAUSED::EXIT
	);

	// Set transition
	set_transition(graphics_objects->transition_ptrs[GRAPHICS_OBJECTS::TRANSITIONS::FADE_TRANSITION]);
}

bool PausedStage::update(float dt) {
	transition->update(dt);

	if (input->just_down(Framework::KeyHandler::Key::ESCAPE) || input->just_down(Framework::KeyHandler::Key::P)) {
		transition->close();
	}

	// Update buttons
	for (Framework::Button& button : buttons) {
		button.update(input);

		if (button.pressed() && transition->is_open()) {
			button_selected = button.get_id();
			transition->close();
		}
	}

	if (transition->is_closed()) {
		if (button_selected == BUTTONS::PAUSED::EXIT) {
			finish(new TitleStage());
		}
		else {
			// Return to game (exit pause)
			finish(_background_stage);
		}
	}

	return true;
}

void PausedStage::render() {
	// Render background stage
	_background_stage->render();

	// Render pause menu
	graphics_objects->graphics_ptr->fill(COLOURS::BLACK, 0x7f);

	for (const Framework::Button& button : buttons) {
		button.render();
	}

	transition->render();
}