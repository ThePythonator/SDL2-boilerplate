#include "Stages.hpp"

// TitleStage

TitleStage::TitleStage() : BaseStage() {

}

void TitleStage::update(float dt, Framework::InputHandler& input) {

}

void TitleStage::render(Framework::Graphics& graphics) {
	graphics.fill(Framework::Colour(0x5F, 0xFF, 0x5F));
}

// GameStage

GameStage::GameStage() : BaseStage() {

}

void GameStage::update(float dt, Framework::InputHandler& input) {

}

void GameStage::render(Framework::Graphics& graphics) {

}

// PausedStage

PausedStage::PausedStage(BaseStage* background_stage) : BaseStage() {
	// Save the background stage so we can still render it, and then go back to it when done
	_background_stage = background_stage;
}

void PausedStage::update(float dt, Framework::InputHandler& input) {
	if (false) {
		// Exit pause
		finish(_background_stage);
	}
}

void PausedStage::render(Framework::Graphics& graphics) {
	// Render background stage
	_background_stage->render(graphics);
}