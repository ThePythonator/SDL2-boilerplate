#include "MenuStages.hpp"

// IntroStage

void IntroStage::start() {
	intro_text = Framework::Text(&graphics_objects->fonts[GRAPHICS_OBJECTS::FONTS::MAIN_FONT], "Some intro text", COLOURS::BLACK);

	intro_timer.stop();

	// Start transition
	set_transition(graphics_objects->transition_ptrs[GRAPHICS_OBJECTS::TRANSITIONS::FADE_TRANSITION].get());
	transition->open();
}

bool IntroStage::update(float dt) {
	transition->update(dt);
	intro_timer.update(dt);

	if (transition->is_open()) {
		if (intro_timer.running()) {
			if (intro_timer.time() >= TIMINGS::INTRO_OPEN_TIME) {
				transition->close();
			}
		}
		else {
			intro_timer.reset();
			intro_timer.start();
		}
	}
	else if (transition->is_closed()) {
		// Finish intro
		finish(new TitleStage());
	}

	return true;
}

void IntroStage::render() {
	graphics_objects->graphics.fill(COLOURS::BLUE);

	// Display some intro text in the centre of the display
	intro_text.render(WINDOW::SIZE_HALF);

	transition->render();
}

// TitleStage

void TitleStage::start() {
	// Create buttons
	buttons.clear();
	buttons.emplace_back(
		Framework::Rect(WINDOW::SIZE_HALF - Framework::Vec(128, 32), Framework::Vec(256, 64)),
		graphics_objects->button_image_groups[GRAPHICS_OBJECTS::BUTTON_IMAGE_GROUPS::STANDARD],
		Framework::Text(&graphics_objects->fonts[GRAPHICS_OBJECTS::FONTS::MAIN_FONT], "Play", COLOURS::BLACK, 4.0f),
		BUTTONS::TITLE::PLAY
	);
	buttons.emplace_back(
		Framework::Rect(WINDOW::SIZE_HALF - Framework::Vec(128, -64), Framework::Vec(256, 64)),
		graphics_objects->button_image_groups[GRAPHICS_OBJECTS::BUTTON_IMAGE_GROUPS::STANDARD],
		Framework::Text(&graphics_objects->fonts[GRAPHICS_OBJECTS::FONTS::MAIN_FONT], "Quit", COLOURS::BLACK, 4.0f),
		BUTTONS::TITLE::QUIT
	);

	// Set transition
	set_transition(graphics_objects->transition_ptrs[GRAPHICS_OBJECTS::TRANSITIONS::FADE_TRANSITION].get());

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
	graphics_objects->graphics.fill(COLOURS::BLUE);

	graphics_objects->graphics.render_circle(Framework::Vec(20, 20), 10, COLOURS::BLACK);
	graphics_objects->graphics.render_rect(Framework::Rect(40, 20, 10, 30), COLOURS::BLACK);

	graphics_objects->spritesheets[GRAPHICS_OBJECTS::SPRITESHEETS::MAIN_SPRITESHEET].sprite(0, Framework::Vec(64, 48));

	graphics_objects->spritesheets[GRAPHICS_OBJECTS::SPRITESHEETS::MAIN_SPRITESHEET].sprite(2, Framework::Vec(16, 48));
	graphics_objects->spritesheets[GRAPHICS_OBJECTS::SPRITESHEETS::MAIN_SPRITESHEET].sprite(2, Framework::Vec(32, 48), Framework::SpriteTransform::ROTATE_90_ACW);

	graphics_objects->spritesheets[GRAPHICS_OBJECTS::SPRITESHEETS::MAIN_SPRITESHEET].sprite(1, Framework::Vec(96, 48), SPRITES::SCALE, _timer.time() * 90);

	for (const Framework::Button& button : buttons) {
		button.render();
	}

	transition->render();
}
