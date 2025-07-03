#pragma once

#include "BaseStage.hpp"

#include "Constants.hpp"

#include "MenuStages.hpp"

#include "Animation.hpp"

class GameStage : public Framework::BaseStage {
public:
	void start();

	bool update(float dt);
	void render();

private:
	std::unique_ptr<Framework::AnimationInterface> spinning_sword;
	std::unique_ptr<Framework::AnimationInterface> big_animation;
};

class PausedStage : public Framework::BaseStage {
public:
	PausedStage(BaseStage* background_stage);

	void start();

	bool update(float dt);
	void render();

private:
	BaseStage* _background_stage;
};
