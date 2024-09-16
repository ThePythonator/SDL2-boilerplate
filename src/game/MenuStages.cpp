#include "MenuStages.hpp"

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
