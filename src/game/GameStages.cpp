#include "GameStages.hpp"

// GameStage

void GameStage::start() {
	// Set transition
	set_transition(graphics_objects->transition_ptrs[GRAPHICS_OBJECTS::TRANSITIONS::FADE_TRANSITION].get());

	// Start transition
	transition->open();

	// Create animation
	Framework::Animation demo_animation = {
		{0, 0.5f, Framework::SpriteTransform::NONE},
		{0, 0.5f, Framework::SpriteTransform::ROTATE_90_CW},
		{0, 0.5f, Framework::SpriteTransform::ROTATE_180_CW},
		{0, 0.5f, Framework::SpriteTransform::ROTATE_270_CW}
	};
	// Create animation handler
	spinning_sword = std::make_unique<Framework::AnimationHandler>(graphics_objects->spritesheets[GRAPHICS_OBJECTS::SPRITESHEETS::MAIN_SPRITESHEET], demo_animation);

	// Create big animation
	Framework::MultiTileAnimation big_multi_animation = {
		{
			{0, 0},
			{
				{4, 1.0f, Framework::SpriteTransform::NONE},
				{8, 0.4f, Framework::SpriteTransform::NONE},
				{12, 0.2f, Framework::SpriteTransform::NONE},
				{8, 0.4f, Framework::SpriteTransform::NONE},
			}
		},
		{
			{16, 0},
			{
				{5, 1.0f, Framework::SpriteTransform::NONE},
				{9, 0.4f, Framework::SpriteTransform::NONE},
				{13, 0.2f, Framework::SpriteTransform::NONE},
				{9, 0.4f, Framework::SpriteTransform::NONE},
			}
		},
		{
			{32, 0},
			{
				{6, 1.0f, Framework::SpriteTransform::NONE},
				{10, 0.4f, Framework::SpriteTransform::NONE},
				{14, 0.2f, Framework::SpriteTransform::NONE},
				{10, 0.4f, Framework::SpriteTransform::NONE},
			}
		},
		{
			{48, 0},
			{
				{7, 1.0f, Framework::SpriteTransform::NONE},
				{11, 0.4f, Framework::SpriteTransform::NONE},
				{15, 0.2f, Framework::SpriteTransform::NONE},
				{11, 0.4f, Framework::SpriteTransform::NONE},
			}
		},
	};
	// Create animation handler
	big_animation = std::make_unique<Framework::MultiTileAnimationHandler>(graphics_objects->spritesheets[GRAPHICS_OBJECTS::SPRITESHEETS::MAIN_SPRITESHEET], big_multi_animation);
}

bool GameStage::update(float dt) {
	transition->update(dt);

	spinning_sword->update(dt);
	big_animation->update(dt);

	if (input->just_down(Framework::KeyHandler::Key::ESCAPE) || input->just_down(Framework::KeyHandler::Key::P)) {
		finish(new PausedStage(this), false);
	}

	return true;
}

void GameStage::render() {
	graphics_objects->graphics.fill(COLOURS::BLUE);

	graphics_objects->spritesheets[GRAPHICS_OBJECTS::SPRITESHEETS::MAIN_SPRITESHEET].sprite(0, Framework::Vec(128, 64));

	spinning_sword->render({ 64, 64 });
	big_animation->render({ 64, 96 });

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
		Framework::Text(&graphics_objects->fonts[GRAPHICS_OBJECTS::FONTS::MAIN_FONT], "Resume", COLOURS::BLACK, 4.0f),
		BUTTONS::PAUSED::RESUME
	);
	buttons.emplace_back(
		Framework::Rect(WINDOW::SIZE_HALF - Framework::Vec(128, -64), Framework::Vec(256, 64)),
		graphics_objects->button_image_groups[GRAPHICS_OBJECTS::BUTTON_IMAGE_GROUPS::STANDARD],
		Framework::Text(&graphics_objects->fonts[GRAPHICS_OBJECTS::FONTS::MAIN_FONT], "Exit", COLOURS::BLACK, 4.0f),
		BUTTONS::PAUSED::EXIT
	);

	// Set transition
	set_transition(graphics_objects->transition_ptrs[GRAPHICS_OBJECTS::TRANSITIONS::FADE_TRANSITION].get());
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
	graphics_objects->graphics.fill(COLOURS::BLACK, 0x7f);

	for (const Framework::Button& button : buttons) {
		button.render();
	}

	transition->render();
}